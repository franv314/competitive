#include <bits/stdc++.h>
using namespace std;

int affetta(int N, int K, string S){
    int ans = 1e9;
    for (char x = 'a'; x <= 'z'; x++) {
        int part = 0;
        for (int i = 0; i < N; i++) {
            if (S[i] != x) {
                part++;
                i += K - 1;
            }
        }
        ans = min(ans, part);
    }
    return ans;
}