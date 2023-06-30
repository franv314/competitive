#include <bits/stdc++.h>
using namespace std;


#define MAXN 200'001

int N, M, K, Q;

int cnt_a = 1, cnt_b = 1;

vector<int> children_a[MAXN], children_b[MAXN];
pair<int, int> dfs_ranges_a[MAXN], dfs_ranges_b[MAXN];

struct Fenwick1D {
    unordered_map<int, long long> arr;

    void update(int x, int d) {
        for (; x <= cnt_a; x += x & -x)
            arr[x] += d;
    }

    long long query(int x) {
        long long ans = 0;
        for (; x; x -= x & -x)
            ans += arr[x];
        return ans;
    }

    Fenwick1D() {
        arr.reserve(1024);
        arr.max_load_factor(0.25);
    }
};

struct Fenwick2D {
    unordered_map<int, Fenwick1D> arr;

    void update(int x, int y, int d) {
        for (; y <= cnt_b; y += y & -y)
            arr[y].update(x, d);
    }

    long long query(int x, int y) {
        long long ans = 0;
        for (; y; y -= y & -y)
            ans += arr[y].query(x);
        return ans;
    }

    Fenwick2D() {
        arr.reserve(1024);
        arr.max_load_factor(0.25);
    }
};

void dfs_a(int node) {
    dfs_ranges_a[node].first = cnt_a;
    for (auto child: children_a[node]) {
        dfs_a(child);
    }
    dfs_ranges_a[node].second = ++cnt_a;
}

void dfs_b(int node) {
    dfs_ranges_b[node].first = cnt_b;
    for (auto child: children_b[node]) {
        dfs_b(child);
    }
    dfs_ranges_b[node].second = ++cnt_b;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 2; i <= N; i++) {
        int PA; cin >> PA;
        children_a[PA].push_back(i);
    }

    cin >> M;
    for (int i = 2; i <= M; i++) {
        int PB; cin >> PB;
        children_b[PB].push_back(i);
    }

    dfs_a(1);
    dfs_b(1);

    Fenwick2D tree;

    cin >> K;
    for (int i = 0; i < K; i++) {
        int X, Y, C; cin >> X >> Y >> C;
        auto [l, r] = dfs_ranges_a[X];
        auto [t, b] = dfs_ranges_b[Y];

        tree.update(l, t, C);
        tree.update(r, t, -C);
        tree.update(l, b, -C);
        tree.update(r, b, C);
    }

    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int U, V; cin >> U >> V;
        auto [l, r] = dfs_ranges_a[U];
        auto [t, b] = dfs_ranges_b[V];

        cout << tree.query(r - 1, b - 1) << endl;
    }
}