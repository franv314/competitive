#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<int> freq(n + 1);
    for (auto x: a) freq[x]++;

    int acc = 0;
    int cutoff = 0;
    while (cutoff < n) {
        if (acc + freq[cutoff + 1] >= k) break;
        acc += freq[++cutoff];
    }

    vector<int> dir;
    for (auto x: a)
        if (x <= cutoff)
            dir.push_back(x);
    vector<int> inv(dir.rbegin(), dir.rend());

    if (dir != inv) {
        return void(cout << "NO\n");
    }

    vector<int> pos(dir.size() + 1);
    int count = 0;
    for (auto x: a) {
        if (x <= cutoff)
            count++;
        if (x == cutoff + 1)
            pos[count]++;
    }

    int len = dir.size();
    for (int i = 0; i < pos.size(); i++) {
        len += min(pos[i], pos[dir.size() - i]);
    }

    if (len >= k - 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
