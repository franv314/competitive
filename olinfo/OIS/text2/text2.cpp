#include <bits/stdc++.h>
using namespace std;

#define MAXK 100'000

int has[MAXK][26];

int main() {
    int N, K; cin >> N >> K;

    vector<string> S(N);
    for (auto &x: S) {
        cin >> x;
        for (int i = 0; i < K; i++) {
            has[i][x[i] - 'a']++;
        }
    }

    int ma = INT_MIN, idx;
    for (int j = 0; j < N; j++) {
        int curr = 0;
        for (int i = 0; i < K; i++) {
            curr += has[i][S[j][i] - 'a'];
        }
        if (curr > ma) {
            ma = curr;
            idx = j;
        }
    }
    cout << idx;
}