#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;

    map<char, set<int>> m;
    for (int i = 0; i < s.size(); i++) {
        m[s[i]].insert(i);
    }
    m['A'].insert(s.size());
    m['T'].insert(s.size());
    m['G'].insert(s.size());
    m['C'].insert(s.size());

    string ans;
    int pos = -1;
    for (;;) {
        auto it1 = make_pair(*m['A'].upper_bound(pos), 'A');
        auto it2 = make_pair(*m['T'].upper_bound(pos), 'T');
        auto it3 = make_pair(*m['C'].upper_bound(pos), 'C');
        auto it4 = make_pair(*m['G'].upper_bound(pos), 'G');

        char c;
        tie(pos, c) = max({it1, it2, it3, it4});
        ans += c;

        if (pos == s.size()) break;
    }

    cout << ans << '\n';
}