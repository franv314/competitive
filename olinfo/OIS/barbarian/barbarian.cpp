#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

#define MAXN 1'000'000

template<bool inv>
struct Segment {
    vector<i64> arr;
    int s;

    void update(int l, i64 x, int n, int nb, int ne) {
        if (nb > l || ne <= l) return;
        if (nb + 1 == ne) return void(arr[n] = x);
        if (l < (nb + ne) / 2) update(l, x, 2 * n, nb, (nb + ne) / 2);
        else update(l, x, 2 * n + 1, (nb + ne) / 2, ne);
        arr[n] = inv ? min(arr[2 * n], arr[2 * n + 1]) : max(arr[2 * n], arr[2 * n + 1]);
    }

    int query(int l, int r, i64 x, int n, int nb, int ne) {
        if (nb >= r || ne <= l || ((inv && arr[n] > x) || (!inv && arr[n] < x))) return -1;
        if (nb + 1 == ne) return nb;
        int fv = inv ? query(l, r, x, 2 * n, nb, (nb + ne) / 2) : query(l, r, x, 2 * n + 1, (nb + ne) / 2, ne);
        if (fv != -1) return fv;
        return inv ? query(l, r, x, 2 * n + 1, (nb + ne) / 2, ne) : query(l, r, x, 2 * n, nb, (nb + ne) / 2);
    }

    void update(int l, i64 x) {
        update(l, x, 1, 0, s);
    }

    int query(int l, int r, i64 x) {
        return query(l, r, x, 1, 0, s);
    }

    Segment(int S) {
        s = 1 << (int)ceil(log2(S));
        arr.resize(2 * s);
    }
};

struct DSU {
    vector<int> arr;

    int find(int node) {
        if (arr[node] < 0) return node;
        return arr[node] = find(arr[node]); 
    }

    void join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;

        if (arr[u] > arr[v]) swap(u, v);
        arr[u] += arr[v];
        arr[v] = u;
    }

    DSU(int size) : arr(size, -1) {
        arr[0] = arr.back() = -1e7;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int N; cin >> N;
    vector<i64> A(N);
    for (auto &a: A) cin >> a;

    Segment<0> pref_seg(N);
    Segment<1> suff_seg(N);

    for (int i = 0; i < N; i++) {
        i64 nxt = i == N - 1 ? +1e16 : A[i + 1];
        i64 prv = i == 0     ? -1e16 : A[i - 1];

        suff_seg.update(i, A[i] - (nxt - A[i]));
        pref_seg.update(i, A[i] + (A[i] - prv) - 1);
    }

    DSU dsu(N);
    vector<signed char> ans(N, -1);

    for (int i = 1; i < N - 1; i++) {
        int l, r, curr;
        i64 nxt = i == N - 1 ? +1e16 : A[i + 1];
        i64 prv = i == 0     ? -1e16 : A[i - 1];
        if (A[i] - prv <= nxt - A[i]) {
            l = curr = i - 1;
            r = i + 1;
        } else {
            r = curr = i + 1;
            l = i - 1;
        }

        if (l == curr) {
            i64 nxt = r == N ? +1e15 : A[r];
            int jmp = pref_seg.query(0, l + 1, nxt);
            dsu.join(jmp, i);
        } else {
            i64 prv = l == -1 ? -1e15 : A[l];
            int jmp = suff_seg.query(r, N, prv);
            dsu.join(jmp, i);
        }
    }
    
    ans[0] = 1;
    ans[N - 1] = 0;
    for (int i = 1; i < N - 1; i++) {
        if (ans[i] != -1) continue;
        vector<int> st;
        int curr = i;
        for (;;) {
            st.push_back(curr);
            if (ans[curr] != -1) break;
            curr = dsu.arr[curr];
        }
        for (auto x: st) ans[x] = ans[curr];
    }

    for (int i = 0; i < N; i++) cout << ans[i] * (N - 1) << ' ';
    cout << '\n';
}