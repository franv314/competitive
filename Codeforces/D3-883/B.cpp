#include <bits/stdc++.h>
using namespace std;

void solve() {
    vector<string> g(3);
    for (auto &x: g) cin >> x;
    
    if (g[0][0] == g[0][1] && g[0][1] == g[0][2] && g[0][0] != '.') return void(cout << g[0][0] << '\n');
    if (g[1][0] == g[1][1] && g[1][1] == g[1][2] && g[1][0] != '.') return void(cout << g[1][0] << '\n');
    if (g[2][0] == g[2][1] && g[2][1] == g[2][2] && g[2][0] != '.') return void(cout << g[2][0] << '\n');
    if (g[0][0] == g[1][0] && g[1][0] == g[2][0] && g[0][0] != '.') return void(cout << g[0][0] << '\n');
    if (g[0][1] == g[1][1] && g[1][1] == g[2][1] && g[0][1] != '.') return void(cout << g[0][1] << '\n');
    if (g[0][2] == g[1][2] && g[1][2] == g[2][2] && g[0][2] != '.') return void(cout << g[0][2] << '\n');
    if (g[0][0] == g[1][1] && g[1][1] == g[2][2] && g[0][0] != '.') return void(cout << g[0][0] << '\n');
    if (g[0][2] == g[1][1] && g[1][1] == g[2][0] && g[0][2] != '.') return void(cout << g[0][2] << '\n');
    cout << "DRAW\n";
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}