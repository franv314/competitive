#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    string t; cin >> t;

    string st = t + "$" + s;

    vector<int> z(st.size());
    int l = 0, r = 0;
    for (int i = 1; i < st.size(); i++) {
        if (i <= r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < st.size() && st[i + z[i]] == st[z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }

    cout << count(z.begin(), z.end(), t.size()) << '\n';
}