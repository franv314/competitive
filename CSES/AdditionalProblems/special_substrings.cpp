#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;

    vector<int> nxt(s.size(), -1);
    vector<int> dp(s.size() + 1, 0);

    map<char, int> freq;
    map<vector<int>, int> pos;

    for (auto c: s) freq[c];
    for (auto &[c, cnt]: freq) cnt = count(s.begin(), s.end(), c);

    vector<int> diff;
    for (auto it = next(freq.begin()); it != freq.end(); it++) {
        diff.push_back(it->second - freq.begin()->second);
    }
    pos[diff] = s.size();

    for (int i = s.size() - 1; i >= 0; i--) {
        freq[s[i]]--;

        vector<int> diff;
        for (auto it = next(freq.begin()); it != freq.end(); it++) {
            diff.push_back(it->second - freq.begin()->second);
        }

        if (pos.count(diff)) nxt[i] = pos[diff];

        pos[diff] = i;
    }

    for (int i = s.size() - 1; i >= 0; i--) {
        if (nxt[i] == -1) continue;
        dp[i] = 1 + dp[nxt[i]];
    }

    cout << accumulate(dp.begin(), dp.end(), 0LL) << '\n';
}