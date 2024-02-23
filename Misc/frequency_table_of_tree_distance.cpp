#include <bits/stdc++.h>
using namespace std;

#define MAXL 19
typedef long long i64;

constexpr int M1 = 5767169;
constexpr int R1 = 177147;
constexpr int I1 = 5087924;
constexpr int V1 = 2883585;

constexpr int M2 = 7340033;
constexpr int R2 = 4782969;
constexpr int I2 = 3821501;
constexpr int V2 = 3670017;

constexpr i64 X = 14110376678738;
constexpr i64 Y = 28220834097840;

int r1[MAXL + 1], i1[MAXL + 1], v1[MAXL + 1], r2[MAXL + 1], i2[MAXL + 1], v2[MAXL + 1];
int temp[1 << MAXL];
int next_2[1 << MAXL];

void precalc() {
    r1[0] = R1, i1[0] = I1, v1[0] = 1;
    r2[0] = R2, i2[0] = I2, v2[0] = 1;
    for (int i = 1; i <= MAXL; i++) {
        r1[i] = (i64)r1[i - 1] * r1[i - 1] % M1;
        i1[i] = (i64)i1[i - 1] * i1[i - 1] % M1;
        v1[i] = (i64)v1[i - 1] * V1 % M1;
        r2[i] = (i64)r2[i - 1] * r2[i - 1] % M2;
        i2[i] = (i64)i2[i - 1] * i2[i - 1] % M2;
        v2[i] = (i64)v2[i - 1] * V2 % M2;
    }

    int old_2 = 0;
    for (int i = 0; i < (1 << MAXL); i++) {
        next_2[i] = old_2;
        if (__builtin_popcount(i) == 1) old_2++;
    }
}

template<bool inv>
void ntt1(int arr[], int start, int step, int size, int depth) {
    if (size == 1) return;

    ntt1<inv>(arr, start       , step * 2, size / 2, depth + 1);
    ntt1<inv>(arr, start + step, step * 2, size / 2, depth + 1);

    for (int i = 0; i < size; i++) temp[i] = arr[start + i * step];

    int c = 1;
    int w = inv ? i1[depth] : r1[depth];

    for (int i = 0; i < size / 2; i++) {
        arr[start + i * step] =
            (temp[2 * i] + (i64)c * temp[2 * i + 1]) % M1;
        arr[start + (i + size / 2) * step] =
            (temp[2 * i] + (M1 - ((i64)c * temp[2 * i + 1]) % M1) % M1) % M1;

        c = (i64)w * c % M1;
    }
}

template<bool inv>
void ntt2(int arr[], int start, int step, int size, int depth) {
    if (size == 1) return;

    ntt2<inv>(arr, start       , step * 2, size / 2, depth + 1);
    ntt2<inv>(arr, start + step, step * 2, size / 2, depth + 1);

    for (int i = 0; i < size; i++) temp[i] = arr[start + i * step];

    int c = 1;
    int w = inv ? i2[depth] : r2[depth];

    for (int i = 0; i < size / 2; i++) {
        arr[start + i * step] =
            (temp[2 * i] + (i64)c * temp[2 * i + 1]) % M2;
        arr[start + (i + size / 2) * step] =
            (temp[2 * i] + (M2 - ((i64)c * temp[2 * i + 1]) % M2) % M2) % M2;

        c = (i64)w * c % M2;
    }
}

vector<i64> convolve(const vector<int> &A) {
    int ans_size = 2 * A.size() - 1;
    int nxt = next_2[ans_size];

    vector<int> A1 = A, A2 = A;
    A1.resize(1 << nxt);
    A2.resize(1 << nxt);

    {
        ntt1<false>(A1.data(), 0, 1, 1 << nxt, MAXL - nxt);
        for (auto &x: A1) x = (i64)x * x % M1;
        ntt1<true>(A1.data(), 0, 1, 1 << nxt, MAXL - nxt);
        for (auto &x: A1) x = (i64)x * v1[nxt] % M1;
    }
    {
        ntt2<false>(A2.data(), 0, 1, 1 << nxt, MAXL - nxt);
        for (auto &x: A2) x = (i64)x * x % M2;
        ntt2<true>(A2.data(), 0, 1, 1 << nxt, MAXL - nxt);
        for (auto &x: A2) x = (i64)x * v2[nxt] % M2;
    }
    
    vector<i64> ans(ans_size);
    for (int i = 0; i < ans_size; i++) {
        ans[i] = ((__int128_t)A1[i] * X + (__int128_t)A2[i] * Y) % ((i64)M1 * M2);
    }

    return ans;
}

struct Tree {
    int N;
    vector<vector<int>> adj;
    vector<int> size;
    vector<bool> used;

    vector<int> cnt;
    vector<i64> ans;

    void get_size(int node, int par = -1) {
        size[node] = 1;
        for (auto x: adj[node]) {
            if (x == par || used[x]) continue;
            get_size(x, node);
            size[node] += size[x];
        }
    }

    void get_depth(int node, int par = -1, int d = 0) {
        cnt[d]++;
        for (auto x: adj[node]) {
            if (x == par || used[x]) continue;
            get_depth(x, node, d + 1);
        }
    }

    void decompose(int root) {
        get_size(root);

        int centroid = root;
pos:
        for (auto x: adj[centroid]) {
            if (size[x] < size[centroid] && 2 * size[x] > size[root]) {
                centroid = x;
                goto pos;
            }
        }

        vector<i64> tmp(size[root]);

        cnt.assign(size[root], 0);
        get_depth(centroid);
        
        vector<i64> cv = convolve(cnt);
        for (int i = 0; i < size[root]; i++) tmp[i] += cv[i];

        for (auto x: adj[centroid]) {
            if (used[x]) continue;
            
            int sz = 1 + (size[x] < size[centroid] ? size[x] : size[root] - size[centroid]);
            cnt.assign(sz, 0);
            get_depth(x, centroid, 1);

            vector<i64> cv = convolve(cnt);

            for (int i = 0; i < min((int)cv.size(), size[root]); i++) tmp[i] -= cv[i];
        } 

        for (int i = 0; i < size[root]; i++) ans[i] += tmp[i] / 2;

        used[centroid] = true;
        for (auto x: adj[centroid]) {
            if (used[x]) continue;
            decompose(x);
        }
    }

    Tree(int N, vector<vector<int>> &&adj) : N(N), adj(adj), size(N), used(N), ans(N) {
        decompose(0);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    precalc();

    int N; cin >> N;
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    Tree tree(N, std::move(adj));
    for (int i = 1; i < N; i++) cout << tree.ans[i] << ' '; cout << '\n';
}