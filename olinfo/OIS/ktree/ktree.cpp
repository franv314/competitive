#include <bits/stdc++.h>
using namespace std;

#define MAXN 250'001

int V[MAXN];
vector<int> children[MAXN];

int path[MAXN];
int path_size;
int lift[MAXN][20];
int lift_size[MAXN];
int depth[MAXN];

struct Node {
    int sum;
    int nb, ne;
    Node *lc, *rc;

    Node() { }
    Node(int nb, int ne, Node *lc, Node *rc, int sum = 0) :
        sum(sum), nb(nb), ne(ne), lc(lc), rc(rc) { }
};

Node pool[6'000'000];
int no;

Node* get(int nb, int ne, Node *lc, Node *rc, int sum = 0) {
    pool[no] = Node(nb, ne, lc, rc, sum);
    return &pool[no++];
}

struct SegTree {
    Node *roots[MAXN];

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) return get(nb, ne, NULL, NULL);
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        return get(nb, ne, lc, rc);
    }

    Node* add(int x, Node *node) {
        if (node->nb > x || node->ne <= x) return node;
        if (node->nb + 1 == node->ne) {
            return get(node->nb, node->ne, NULL, NULL, node->sum + 1);
        }
        Node *lc = add(x, node->lc);
        Node *rc = add(x, node->rc);
        return get(node->nb, node->ne, lc, rc, lc->sum + rc->sum);
    }

    int query_path(int M, Node *u, Node *v, Node *l, Node *pl) {
		if (u->nb + 1 == u->ne) return u->nb;
		int count = u->rc->sum + v->rc->sum - l->rc->sum - pl->rc->sum;
		if (count >= M) {
			return query_path(M, u->rc, v->rc, l->rc, pl->rc);
		} else {
			return query_path(M - count, u->lc, v->lc, l->lc, pl->lc);
		}
	}

public:

    void add_node(int node, int val) {
        roots[node] = add(val, roots[lift[node][0]]);
    }

    int query_path(int u, int v, int l, int pl, int M) {
		return query_path(M, roots[u], roots[v], roots[l], roots[pl]);
	}

    SegTree() {
        roots[0] = build(0, MAXN);
    }
} segtree;

void dfs(int node) {
    depth[node] = path_size;
    path[path_size++] = node;
    int h = 0;
    for (int i = 1; i < path_size; i <<= 1, h++) {
        lift[node][h] = path[path_size - 1 - i];
    }
    lift_size[node] = h;

    segtree.add_node(node, V[node]);

    for (auto child: children[node]) {
        dfs(child);
    }

    path_size--;
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);

    for (int i = lift_size[v] - 1; i >= 0; i--) {
        if (lift_size[v] > i && depth[lift[v][i]] >= depth[u]) {
            v = lift[v][i];
        }
    }
    
    if (u == v) return u;

    for (int i = lift_size[u] - 1; i >= 0; i--) {
        if (lift_size[u] > i && lift[u][i] != lift[v][i]) {
            u = lift[u][i];
            v = lift[v][i];
        }
    }
    return lift[u][0];
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> V[i];
    }

    for (int i = 2; i <= N; i++) {
        int P; cin >> P;
        children[P].push_back(i);
    }

    depth[0] = -1;
    lift[1][0] = 0;
    lift_size[1] = 1;
    dfs(1);

    int Q; cin >> Q;
    while (Q--) {
        int u, v, k; cin >> u >> v >> k;
        int l = lca(u, v);
		int pl = lift[l][0];

        cout << segtree.query_path(u, v, l, pl, k) << '\n';
    }
}