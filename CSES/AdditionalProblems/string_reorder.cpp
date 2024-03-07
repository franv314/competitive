#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;

    int freq[26] = {};
    for (auto c: s) freq[c - 'A']++;

    for (auto f: freq) {
        if (f > (s.size() + 1) / 2) {
            cout << "-1\n";
            return 0;
        }
    }

    string ans;
    for (int i = 0; i < s.size(); i++) {
        int *ptr = max_element(freq, freq + 26);

        if (*ptr > (s.size() - i) / 2) {
            ans.push_back(ptr - freq + 'A');
            --*ptr;
        } else {
            for (int j = 0; j < 26; j++) {
                if (freq[j] && (ans.empty() || ans.back() != j + 'A')) {
                    ans.push_back(j + 'A');
                    freq[j]--;
                    break;
                }
            }
        }
    }

    cout << ans << '\n';
}