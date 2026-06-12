#include <bits/stdc++.h>
using namespace std;

struct Info {
    int sum, max_pref;
    Info(int sum, int max_pref) : sum(sum), max_pref(max_pref) { }
    Info(int val) : Info(val, max(0, val)) { }
    Info() : Info(0) { }
};

Info merge(const Info &a, const Info &b) {
    return Info(a.sum + b.sum, max(a.max_pref, a.sum + b.max_pref));
}

struct SegTree {
    vector<Info> arr;
    int s;

    void upd(int pos, int val) {
        arr[pos += s] = Info(val);
        for (pos >>= 1; pos; pos >>= 1)
            arr[pos] = merge(arr[2 * pos], arr[2 * pos + 1]);
    }

    int qry() { return arr[1].max_pref; }

    void reset() {
        for (auto &x: arr) x = Info();
    }

    SegTree(int N) {
        s = 1 << (int)ceil(log2(N));
        arr.resize(2 * s);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<int> h(k);
    for (auto &x: h) cin >> x;
    vector<vector<int>> grid(n, vector<int>(m));
    for (auto &row: grid)
        for (auto &el: row)
            cin >> el;

    int ans = 0;
    SegTree st(m + k);

    vector<int> maxh(m);
    for (int i = 0; i < n; i++) {
        vector<pair<int, int>> compress;
        for (int j = 0; j < m; j++)
            compress.emplace_back(maxh[j], j);
        for (int j = 0; j < k; j++)
            compress.emplace_back(h[j], -(j + 1));
        sort(compress.begin(), compress.end());
        st.reset();
        
        vector<int> bh(k), br(m);
        for (int i = 0; i < compress.size(); i++) {
            if (compress[i].second < 0) bh[-compress[i].second - 1] = i;
            else br[compress[i].second] = i;
        }

        for (int i = 0; i < k; i++) {
            st.upd(br[i], -1);
        }
        for (int i = 0; i < k; i++) {
            st.upd(bh[i], 1);
        }

        int free = count(grid[i].begin(), grid[i].begin() + k, 0);
        for (int s = 0; s <= m - k; s++) {
            if (free == k) {
                ans += st.qry() == 0;
            }

            free -= grid[i][s] == 0;
            st.upd(br[s], 0);
            if (s + k != m) {
                st.upd(br[s + k], -1);
                free += grid[i][s + k] == 0;
            }
        }

        for (int j = 0; j < m; j++)
            maxh[j] = max(maxh[j], grid[i][j]);
    }

    cout << ans << '\n';
}
