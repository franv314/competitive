#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
    vector<vector<int>> table;

    int query(int l, int r) {
        int h = log2(r - l);
        return min(table[h][l], table[h][r - (1 << h)]);
    }

    SparseTable(const vector<int> &arr) {
        table.push_back(arr);
        for (int h = 1; (1 << h) <= arr.size(); h++) {
            table.emplace_back(arr.size());
            for (int i = 0; i < arr.size(); i++) {
                table[h][i] = min(table[h - 1][i], table[h - 1][min((int)arr.size(), i + (1 << (h - 1)))]);
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    SparseTable st(a);

    while (q--) {
        int l, r; cin >> l >> r;
        cout << st.query(l - 1, r) << '\n';
    }
}