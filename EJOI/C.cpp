#include <bits/stdc++.h>
using namespace std;

struct Info : vector<int> {
    Info() : vector() { }
    Info(int N) : vector(N) { iota(begin(), end(), 0); }
    Info(int N, pair<int, int> edge) : Info(N) {
        (*this)[edge.first] = edge.second;
    }
};

Info merge(int N, Info l, Info r) {
    Info info(N);
    for (int i = 0; i < N; i++)
        info[i] = r[l[i]];
    return info;
}

struct SegTree {
    vector<Info> arr;
    int N, s;

    void update(int p, pair<int, int> edge) {
        arr[p += s] = Info(N, edge);
        for (p >>= 1; p; p >>= 1)
            if (!arr[2 * p + 1].empty())
                arr[p] = merge(N, arr[2 * p], arr[2 * p + 1]);
    }

    Info query(int l, int r) {
        Info ans_l = Info(N), ans_r = Info(N);
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans_l = merge(N, ans_l, arr[l++]);
            if (r & 1) ans_r = merge(N, arr[--r], ans_r);
        }
        return merge(N, ans_l, ans_r);
    }

    SegTree(int N, int K, const vector<pair<int, int>> &a) : N(N) {
        s = 1 << (int)ceil(log2(K));
        arr.resize(2 * s);

        for (int i = 0; i < K; i++)
            arr[i + s] = Info(N, a[i]);
        for (int i = s - 1; i; i--)
            if (!arr[2 * i + 1].empty())
                arr[i] = merge(N, arr[2 * i], arr[2 * i + 1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    
    int N, M; cin >> N >> M;
    vector<pair<int, int>> edges(M);
    for (auto &[u, v]: edges) {
        cin >> u >> v;
        u--, v--;
    }

    int K; cin >> K;
    vector<pair<int, int>> arr(K);
    for (auto &el: arr) {
        int i; cin >> i;
        el = edges[i - 1];
    }

    SegTree segtree(N, K, arr);

    int Q; cin >> Q;
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, s; cin >> l >> r >> s;
            l--, s--;
            cout << segtree.query(l, r)[s] + 1 << '\n';
        } else {
            int i, k; cin >> i >> k;
            i--, k--;
            segtree.update(i, edges[k]);
        }
    }
}
