#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct Hash {
    function<int(int, char)> extend_hash;

    int hash(string s) {
        return accumulate(s.begin(), s.end(), 1, extend_hash);
    }

    Hash(int m, int a) {
        extend_hash = [=](int curr_hash, char c) -> int {
            return ((long long)curr_hash * a + c - 48) % m;
        };
    }
};

Hash h1(885620119, 208118241);
Hash h2(720139531, 694422976);

int main() {
    int N, M; cin >> N >> M;
    string S; cin >> S;

    unordered_set<long long> hashes;

    for (int i = 0; i < M; i++) {
        string t; cin >> t;
        hashes.insert((long long)h1.hash(t) << 32 | h2.hash(t));
    }

    vector<int> dp(N + 1);
    dp[N] = 1;
    for (int i = N - 1; i >= 0; i--) {
        long long curr_hash_1 = 1, curr_hash_2 = 1;
        for (int j = i; j < N; j++) {
            curr_hash_1 = h1.extend_hash(curr_hash_1, S[j]);
            curr_hash_2 = h2.extend_hash(curr_hash_2, S[j]);
            if (hashes.find(curr_hash_1 << 32 | curr_hash_2) != hashes.end()) {
                dp[i] = (dp[i] + dp[j + 1]) % MOD;
            }
        }
    }
    cout << dp[0];
}