#include <bits/stdc++.h>
using namespace std;

int monete(int N, int v[]) {
    int ma = 0;
    for (int i = 2; i <= N; i++) {
        map<int, int> freq;
        for (int j = i; j <= N; j += i) {
            freq[v[j - 1]]++;
        }

        for (auto [_, f]: freq) {
            ma = max(ma, f);
        }
    }
    return ma;
}