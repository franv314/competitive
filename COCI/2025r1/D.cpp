#include <bits/stdc++.h>
using namespace std;

constexpr int MAXK = 4;

struct Upd {
    int x, t, b;
    int type;
};

class SegTree {
    struct Info {
        array<int, MAXK> has;
        array<int, 1 << MAXK> total;
    };  

    vector<Info> arr;
    int k;
    int s;

    void pull(int n, int nb, int ne) {
        if (ne - nb == 1) {
            int mask = 0;
            for (int i = 0; i < k; i++)
                if (arr[n].has[i])
                    mask |= (1 << i);
            
            arr[n].total = array<int, 1 << MAXK>();
            arr[n].total[mask] = 1;

            return;
        }

        for (int i = 0; i < (1 << k); i++) {
            arr[n].total[i] = arr[2 * n].total[i] + arr[2 * n + 1].total[i];
        }

        for (int i = 0; i < k; i++) {
            if (!arr[n].has[i]) continue;

            for (int mask = 0; mask < (1 << k); mask++) {
                if ((mask >> i) & 1) {
                    arr[n].total[mask] += arr[n].total[mask ^ (1 << i)];
                    arr[n].total[mask ^ (1 << i)] = 0;
                }
            }
        }
    }

    void update(int l, int r, int t, int n, int nb, int ne) {
        if (l >= ne || r <= nb) return;
        if (l <= nb && ne <= r) {
            if (t > 0)
                arr[n].has[abs(t) - 1]++;
            if (t < 0)
                arr[n].has[abs(t) - 1]--;

            return pull(n, nb, ne);
        }

        update(l, r, t, 2 * n, nb, (nb + ne) / 2);
        update(l, r, t, 2 * n + 1, (nb + ne) / 2, ne);
        pull(n, nb, ne);
    }

public:

    int query() { return arr[1].total[(1 << k) - 1]; }
    void update(int l, int r, int t) { update(l, r, t, 1, 0, s); }

    SegTree(int n, int k) : k(k) {
        s = 1 << (int)ceil(log2(n));
        arr.resize(2 * s);

        for (int i = 0; i < n; i++)
            arr[i + s].total[0] = 1;
        for (int i = s - 1; i > 0; i--)
            arr[i].total[0] = arr[2 * i].total[0] + arr[2 * i + 1].total[0];
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<vector<int>> pos(n);
    for (int i = 0; i < n; i++)
        pos[i].push_back(-1);
    for (int i = 0; i < n; i++)
        pos[a[i] - 1].push_back(i);
    for (int i = 0; i < n; i++)
        pos[i].push_back(n);

    vector<Upd> upds;
    for (int i = 0; i < n; i++) {
        for (int l = 1; l <= k; l++) {
            for (int j = 1; j + l < pos[i].size(); j++) {
                int prv = pos[i][j - 1];
                int fst = pos[i][j];
                int lst = pos[i][j + l - 1];
                int nxt = pos[i][j + l];

                upds.push_back({prv + 1, lst, nxt, +l});
                upds.push_back({fst + 1, lst, nxt, -l});
            }
        }
    }

    sort(upds.begin(), upds.end(), [](const auto &a, const auto &b) { return a.x < b.x; });

    int last_x = 0;
    long long ans = 0;
    SegTree segtree(n, k);

    for (auto [x, l, r, t]: upds) {
        ans += (long long)(x - last_x) * segtree.query();
        
        segtree.update(l, r, t);
        last_x = x;
    }

    cout << ans << '\n';
}