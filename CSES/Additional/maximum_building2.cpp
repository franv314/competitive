#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct Node {
    i64 m = 0, q = 0;
    i64 sum = 0;
};

struct SegTree {
    vector<Node> arr;
    int s;

    void push(int n, int nb, int ne) {
        if (arr[n].m == 0 && arr[n].q == 0) return;
        
        i64 add = arr[n].m * (ne * (ne - 1) / 2 - nb * (nb - 1) / 2) 
                + arr[n].q * (ne - nb);
        arr[n].sum += add;

        if (nb + 1 != ne) {
            arr[2 * n].m += arr[n].m;
            arr[2 * n].q += arr[n].q;
            arr[2 * n + 1].m += arr[n].m;
            arr[2 * n + 1].q += arr[n].q;
        }

        arr[n].m = 0;
        arr[n].q = 0;
    }

    void update(int l, int r, int m, int q, int n, int nb, int ne) {
        push(n, nb, ne);
        if (nb >= r || ne <= l) return;
        if (l <= nb && ne <= r) {
            arr[n].m += m;
            arr[n].q += q;
            push(n, nb, ne);
            return;
        }

        update(l, r, m, q, 2 * n, nb, (nb + ne) / 2);
        update(l, r, m, q, 2 * n + 1, (nb + ne) / 2, ne);
        arr[n].sum = arr[2 * n].sum + arr[2 * n + 1].sum;
    }

    i64 query(int l, int r, int n, int nb, int ne) {
        push(n, nb, ne);
        if (nb >= r || ne <= l) return 0;
        if (l <= nb && ne <= r) return arr[n].sum;
        return query(l, r, 2 * n, nb, (nb + ne) / 2) + query(l, r, 2 * n + 1, (nb + ne) / 2, ne);
    }

public:

    void update(int l, int r, int m, int q) { update(l, r, m, q, 1, 0, s); }
    i64 query(int l, int r) { return query(l, r, 1, 0, s); }
    SegTree() { }
    SegTree(int size) {
        s = 1 << (int)ceil(log2(size));
        arr.resize(2 * s);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto &row: grid) cin >> row;

    vector<vector<int>> ans(n + 1, vector<int>(m));
    vector<SegTree> segtrees(n + 1);
    for (int i = 0; i <= n; i++) {
        segtrees[i] = SegTree(m + 1);
    }

    vector<int> block(m, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '*') {
                block[j] = i;
            }
        }

        stack<pair<int, int>> st;
        st.emplace(-1, i);
        for (int j = 0; j < m; j++) {
            while (!st.empty() && st.top().second <= block[j]) {
                auto [_, h1] = st.top(); st.pop();
                
                if (st.empty()) break;
                auto [x, h2] = st.top();

                segtrees[i - min(h2, block[j])].update(1, j - x, +1, x - j);
                segtrees[i - h1].update(1, j - x, -1, j - x);
            }
            st.emplace(j, block[j]);
        }
        
        while (st.size() > 1) {
            auto [_, h1] = st.top(); st.pop();

            auto [x, h2] = st.top();

            segtrees[i - h2].update(1, m - x, +1, x - m);
            segtrees[i - h1].update(1, m - x, -1, m - x);
        }
    }


    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            ans[i][j] = ans[i + 1][j] + segtrees[i + 1].query(j + 1, j + 2);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
}