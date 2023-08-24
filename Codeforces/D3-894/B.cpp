#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> seq;
    int last = 1;
    while (n--) {
        int v; cin >> v;
        if (v < last) {
            seq.push_back(1);
        }
        seq.push_back(v);
        last = v;
    }
    cout << seq.size() << '\n';
    for (auto x: seq) cout << x << " "; cout << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}