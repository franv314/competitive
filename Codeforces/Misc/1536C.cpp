#include <bits/stdc++.h>
using namespace std;

pair<int, int> reduce(int p, int q) {
    if (p == 0) return {0, 1};
    if (q == 0) return {1, 0};
    int g = gcd(p, q);
    return {p / g, q / g};
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    
    int d = 0, k = 0;
    map<pair<int, int>, int> freqs;
    for (auto c: s) {
        d += c == 'D';
        k += c == 'K';
        pair<int, int> ratio = reduce(d, k);
        cout << ++freqs[ratio] << ' ';
    }
    cout << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}