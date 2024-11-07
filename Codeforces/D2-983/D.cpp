#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    int q = 0;

    auto qry = [&](int x, int y) {
        q++;
        cout << "? " << x << " " << y << endl;
        int ans; cin >> ans;
        return ans;
    };

    auto ans = [](vector<int> ans) {
        cout << "! ";
        for (auto x: ans)
            cout << x << " ";
        cout << endl;
    };

    int i;
    vector<int> p(n);

    for (i = 2; i < n; i++)
        if (!qry(i, 1))
            break;
    p[i] = 1;

    int last = 2;
    for (i++; i < n; i++) {
        while (last < i - 1 && qry(i, last))
            last++;
        p[i] = last++;
    }

    cerr << "Queries: " << q << '\n';
    ans(vector<int>(p.begin() + 1, p.end()));
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}
