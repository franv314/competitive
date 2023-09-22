#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s; cin >> s;
    vector<int> blocks;

    int l = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'B') {
            blocks.push_back(i - l);
            l = i + 1;
        }
    }
    blocks.push_back(s.size() - l);

    cout << accumulate(blocks.begin(), blocks.end(), 0LL) - *min_element(blocks.begin(), blocks.end()) << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}