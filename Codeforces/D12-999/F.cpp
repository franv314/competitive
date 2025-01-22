#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s, t; cin >> s >> t;

    auto blocks = [](const string &s) -> deque<pair<bool, int>> {
        deque<pair<bool, int>> ans;

        int l = 0;
        for (int i = 1; i <= s.size(); i++) {
            if (i == s.size() || s[i - 1] != s[i]) {
                ans.emplace_back(s[i - 1] == '1', i - l);
                l = i;
            }
        }

        return ans;
    };

    deque<pair<bool, int>> s_blocks = blocks(s);
    deque<pair<bool, int>> t_blocks = blocks(t);

    int ans = 0;

    while (!s_blocks.empty()) {
        if (t_blocks.empty()) {
            return void(cout << "-1\n");
        }

        auto  [s_type, s_length] = s_blocks[0];
        auto &[t_type, t_length] = t_blocks[0];
        if (t_type == s_type) {
            if (s_length > t_length)
                return void(cout << "-1\n");

            s_blocks.pop_front();
            if (s_length == t_length)
                t_blocks.pop_front();
            else
                t_length -= s_length;
        } else {
            ans++;
            s_blocks.pop_front();
            if (s_blocks.size() == 1)
                s_blocks.emplace_back(s_type, s_length);
            else
                s_blocks[1].second += s_length;
        }
    }

    if (!t_blocks.empty())
        return void(cout << "-1\n");
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
