#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> small_cases = {
    {},
    {1},
    {1, 2},
    {1, 2, 2},
    {1, 2, 2, 3},
    {1, 2, 2, 3, 3},
};

void solve() {
    int n; cin >> n;
    
    if (n <= 5) {
        cout << small_cases[n].back() << '\n';
        for (auto x: small_cases[n])
            cout << x << ' ';
        cout << '\n';
    } else {
        cout << "4\n";
        for (int i = 0; i < n; i++)
            cout << (i % 4) + 1 << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--)
        solve();
}