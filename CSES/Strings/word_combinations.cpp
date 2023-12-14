#include <bits/stdc++.h>
using namespace std;
 
constexpr int MOD = 1'000'000'007;
constexpr int M = 1'889'971'969;
constexpr int B = 29;
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int m; cin >> m;
 
    vector<set<int>> hashes(s.size() + 1);
    for (int i = 0; i < m; i++) {
        string t; cin >> t;
        int h = 0;
        for (auto c: t) {
            h = ((long long)h * B + c - 'a') % M;
        }
        hashes[t.size()].insert(h);
    }
 
    vector<int> dp(s.size() + 1);
    dp.back() = 1;
 
    for (int i = s.size(); i >= 0; i--) {
        int h = 0;
        for (int j = i; j < s.size(); j++) {
            h = ((long long)h * B + s[j] - 'a') % M;
            if (hashes[j - i + 1].count(h)) (dp[i] += dp[j + 1]) %= MOD;
        }
    }
 
    cout << dp[0] << '\n';
}