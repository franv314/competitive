#include <bits/stdc++.h>
using namespace std;

#define m (l + r) / 2

int controlla(int l, int r);

vector<int> V;

bool contained(int l) {
    unordered_set<int> knowns;
    for (int i = l; i < V.size(); i++)
        knowns.insert(V[i]);
    return knowns.size() == controlla(l, V.size());
}

vector<int> sondaggia(int N) {
    for (int i = 0; i < N; i++) {
        int l = -1, r = i;
        while (l < r - 1) contained(m) ? l = m : r = m;
        V.push_back(l == -1 ? V.size() : V[l]);
    }
    return V;
}