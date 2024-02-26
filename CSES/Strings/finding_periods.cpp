#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;

    vector<int> z(s.size());
    int l = 0, r = 0;
    for (int i = 1; i < s.size(); i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < s.size() && s[i + z[i]] == s[z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }

    for (int len = 1; len <= s.size(); len++) {
        bool ok = true;
        for (int start = len; start < s.size(); start += len) {
            ok &= z[start] >= min(len, (int)s.size() - start);
        }

        if (ok) cout << len << ' ';
    }
    cout << '\n';
}