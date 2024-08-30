#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
    vector<vector<int>> table;
 
    int query(int l, int r) {
        int h = log2(r - l);
        return gcd(table[h][l], table[h][r - (1 << h)]);
    }
 
    SparseTable(const vector<int> &arr) {
        table.push_back(arr);
        for (int h = 1; (1 << h) <= arr.size(); h++) {
            table.emplace_back(arr.size());
            for (int i = 0; i + (1 << (h - 1)) < arr.size(); i++) {
                table[h][i] = gcd(table[h - 1][i], table[h - 1][i + (1 << (h - 1))]);
            }
        }
    }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<int> diffs(n - 1);
    for (int i = 0; i < n - 1; i++)
        diffs[i] = abs(a[i] - a[i + 1]);
    SparseTable st(diffs);

    long long cnt = 0;
    for (int i = 0; i < n; i++) {
        int l = i, r = n;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (__builtin_popcount(st.query(i, m)) == 1) r = m;
            else l = m;
        }

        cnt += n - r;
    }

    for (int l = 0; l < n; l++) {
        int r = l;
        while (r < n && a[r] == a[l]) {
            cnt += r - l + 1;
            r++;
        }
        l = r - 1;
    }

    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}