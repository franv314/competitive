#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    if (count(s.begin(), s.end(), '(') != count(s.begin(), s.end(), ')')) {
        cout << "-1\n";
        return;
    }

    vector<int> ans(n);
    int curr = 0;
    for (int i = 0; i < n; i++) {
        int c = s[i] == '(' ? 1 : -1;
        
        if (curr < 0 || curr + c < 0) ans[i] = 2;
        else ans[i] = 1;

        curr += c;
    }

    if (all_of(ans.begin(), ans.end(), [](int x){ return x == 2; })) {
        fill(ans.begin(), ans.end(), 1);
    }

    cout << *max_element(ans.begin(), ans.end()) << '\n';
    for (auto x: ans) cout << x << " ";
    cout << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}