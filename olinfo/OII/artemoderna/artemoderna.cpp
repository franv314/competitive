#include <bits/stdc++.h>
using namespace std;

bool ordina(int N, vector<int> V, vector<int> &L) {
    int l = 0;
    V.push_back(INT_MAX);
    for (int i = 0; i < N; i++) {
        if (V[i + 1] > V[i]) {
            L.push_back(i + 1 - l);
            reverse(V.begin() + l, V.begin() + i + 1);
            l = i + 1;
        }
    }
    return is_sorted(V.begin(), V.end());
}
