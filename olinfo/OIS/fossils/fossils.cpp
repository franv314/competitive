#include <bits/stdc++.h>
using namespace std;

#define MAXN 200'001

int N, M, K, Q;

struct SegTree {
    struct Node {
        long long sum;
        int nb, ne;
        Node *lc, *rc;

        Node(long long v, int b, int e, Node *l, Node *r) :
            sum(v), nb(b), ne(e), lc(l), rc(r) { }
    } *root;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) {
            return new Node(0, nb, ne, NULL, NULL);
        }
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        return new Node(0, nb, ne, lc, rc);
    }

    void add(int x, int v, Node* node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->sum += v;
            return;
        }
        add(x, v, node->lc);
        add(x, v, node->rc);
        node->sum = node->lc->sum + node->rc->sum;
    }

    long long query(int l, int r, Node* node) {
        if (node->nb >= r || node->ne <= l) return 0;
        if (l <= node->nb && node->ne <= r) return node->sum;
        return query(l, r, node->lc) + query(l, r, node->rc);
    }

public:

    void add(int x, int v) { add(x, v, root); }
    long long query(int l, int r) { return query(l, r, root); }

    SegTree() { root = build(0, MAXN - 1); }

} tree;

vector<int> children_a[MAXN], children_b[MAXN];
vector<pair<int, int>> connections[MAXN], queries[MAXN];

long long answers[MAXN];

pair<int, int> dfs_ranges[MAXN];
int cnt = 0;

void dfs_b(int node) {
    dfs_ranges[node].first = cnt;
    for (auto child: children_b[node])
        dfs_b(child);
    dfs_ranges[node].second = ++cnt;
}

void dfs_a(int node) {
    for (auto [Y, C]: connections[node]) {
        tree.add(dfs_ranges[Y].first, C);
        tree.add(dfs_ranges[Y].second, -C);
    }
    for (auto [i, V]: queries[node]) {
        long long ans = tree.query(0, dfs_ranges[V].second);
        answers[i] = ans;
    }

    for (auto child: children_a[node])
        dfs_a(child);

    for (auto [Y, C]: connections[node]) {
        tree.add(dfs_ranges[Y].first, -C);
        tree.add(dfs_ranges[Y].second, C);
    }
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

    cin >> K;
    for (int i = 0; i < K; i++) {
        int X, Y, C; cin >> X >> Y >> C;
        connections[X].push_back({Y, C});
    }

    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int U, V; cin >> U >> V;
        queries[U].push_back({i, V});
    }

    dfs_b(1);
    dfs_a(1);

    for (int i = 0; i < Q; i++)
        cout << answers[i] << endl;
}