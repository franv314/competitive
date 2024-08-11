#include <bits/stdc++.h>
using namespace std;

struct Info {
    int cnt_yes, last_yes;
    int cnt_no, last_no;

    int fst;
    int mi, mi_pos;

    Info(int cnt_yes, int last_yes, int cnt_no, int last_no, int fst, int mi, int mi_pos) :
        cnt_yes(cnt_yes), last_yes(last_yes), cnt_no(cnt_no), last_no(last_no), fst(fst), mi(mi), mi_pos(mi_pos) { }
    Info(int val, int idx) :
        Info(1, val, 0, 1e9, val, val, idx) { }
    Info() : mi_pos(-1) { }
};

Info merge(const Info &a, const Info &b) {
    if (a.mi_pos == -1) return b;
    if (b.mi_pos == -1) return a;

    int fst = a.fst;

    int cnt_yes, last_yes;
    int cnt_no, last_no;

    if (a.last_yes < b.fst) {
        cnt_yes = a.cnt_yes + b.cnt_no;
        last_yes = b.last_no;
    } else {
        cnt_yes = a.cnt_yes + b.cnt_yes;
        last_yes = b.last_yes;
    }

    if (a.last_no < b.fst) {
        cnt_no = a.cnt_no + b.cnt_no;
        last_no = b.last_no;
    } else {
        cnt_no = a.cnt_no + b.cnt_yes;
        last_no = b.last_yes;
    }

    return {cnt_yes, last_yes, cnt_no, last_no, fst, min(a.mi, b.mi), a.mi < b.mi ? a.mi_pos : b.mi_pos};
}

struct SegTree {
    vector<Info> arr;
    int N;
    int s;

    void update(int p, int v) {
        arr[p + s] = Info(v, p);
        p += s;

        for (p >>= 1; p; p >>= 1)
            arr[p] = merge(arr[2 * p], arr[2 * p + 1]);
    };

    Info query(int l, int r) {
        Info ans_l, ans_r;
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans_l = merge(ans_l, arr[l++]);
            if (r & 1) ans_r = merge(arr[--r], ans_r);
        }
        return merge(ans_l, ans_r);
    }

    int query() {
        int mi = arr[1].mi_pos;
        return N - merge(query(mi, N), query(0, mi)).cnt_yes;
    }

    SegTree(vector<int> a) : N(a.size()) {
        s = 1 << (int)ceil(log2(a.size()));
        arr.resize(2 * s);

        for (int i = 0; i < a.size(); i++)
            arr[i + s] = Info(a[i], i);
        for (int i = s - 1; i > 0; i--)
            arr[i] = merge(arr[2 * i], arr[2 * i + 1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, Q; cin >> N >> Q;

    vector<int> T(N);

    for (int i = 0; i < N; i++) {
        cin >> T[i];
    }

    SegTree segtree(T);

    cout << segtree.query() << ' ';
    while (Q--) {
        int X, C; cin >> X >> C;
        segtree.update(X, C);
        cout << segtree.query() << ' ';
    }
    cout << '\n';
}
