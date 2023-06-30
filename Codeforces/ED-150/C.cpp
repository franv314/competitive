#include <bits/stdc++.h>
using namespace std;

int val[100];

int eval(string s) {
    char max_found = 'A';
    int ans = 0;
    for (auto x: s) {
        if (max_found > x) ans -= val[x];
        else ans += val[x];
        max_found = max(max_found, x);
    }
    return ans;
}

void solve() {
    string s; cin >> s;
    reverse(s.begin(), s.end());

    array<string, 50> possible_strings;

    for (int i = 0; i < 50; i++) {
        possible_strings[i] = s;
    }

    bitset<100> found;
    for (int i = 0; i < s.size(); i++) {
        if (!found[s[i]]) {
            for (int c = 'A'; c <= 'E'; c++) {
                possible_strings[(s[i] - 'A') * 5 + c - 'A'][i] = c;
            }
            found.set(s[i]);
        }
    }

    found.reset();
    for (int i = s.size() - 1; i >= 0; i--) {
        if (!found[s[i]]) {
            for (int c = 'A'; c <= 'E'; c++) {
                possible_strings[25 + (s[i] - 'A') * 5 + c - 'A'][i] = c;
            }
            found.set(s[i]);
        }
    }

    int ma = INT_MIN;
    for (int i = 0; i < 50; i++) ma = max(ma, eval(possible_strings[i]));
    cout << ma << '\n';
}

int main() {
    val['A'] = 1;
    val['B'] = 10;
    val['C'] = 100;
    val['D'] = 1000;
    val['E'] = 10000;

    int t; cin >> t;
    while (t--) solve();
}