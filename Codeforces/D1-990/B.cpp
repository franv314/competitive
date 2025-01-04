#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    map<int, deque<int>> pos;
    for (int i = 0; i < n; i++)
        pos[a[i]].push_back(i);

    vector<int> ok, moved;
    int ptr = 0;
    int mi = 2e9;

    for (auto &[v, l]: pos) {
        if (v > mi + 1) {
            copy(l.begin(), l.end(), back_inserter(moved));
            continue;
        }

        while (!l.empty() && l.front() < ptr) {
            moved.push_back(l.front());
            l.pop_front();
        }

        copy(l.begin(), l.end(), back_inserter(ok));
        for (; ptr <= l.back(); ptr++)
            if (!binary_search(l.begin(), l.end(), ptr))
                mi = min(mi, a[ptr]);
    }

    for (auto x: ok)
        cout << a[x] << ' ';
    sort(moved.begin(), moved.end(), [&](int u, int v) { return a[u] < a[v]; });
    for (auto x: moved)
        cout << a[x] + 1 << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
