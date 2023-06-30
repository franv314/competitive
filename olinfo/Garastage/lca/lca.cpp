#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

#define _ << " " <<
#define MAXN 100000

struct arco_t {
    int dest;
    int peso;
};

class MinTree {
    struct Node {
        int mi;
        int nb, ne;
        Node *lc, *rc;
    } *nodes, *root;
    int node;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) {
            nodes[node] = {0, nb, ne, NULL, NULL};
            return &nodes[node++];
        }
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        nodes[node] = {0, nb, ne, lc, rc};
        return &nodes[node++];
    }

    void update(int x, int v, Node* node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->mi = v;
            return;
        }
        update(x, v, node->lc);
        update(x, v, node->rc);
        node->mi = min(node->lc->mi, node->rc->mi);
    }

    int query(int l, int r, Node* node) {
        if (node->nb >= r || node->ne <= l) return INT_MAX;
        if (l <= node->nb && node->ne <= r) return node->mi;
        return min(query(l, r, node->lc), query(l, r, node->rc));
    }

public:

    int query(int l, int r) {
        return query(l, r, root);
    }

    void update(int x, int v) {
        update(x, v, root);
    }

    MinTree(int N) {
        node = 0;
        nodes = (Node*)malloc(300'000 * sizeof(Node));
        root = build(0, N);
    }
};

class MaxTree {
public:

    struct Node {
        long long sum, max_sub, max_pref, max_suff;
        int nb, ne;
        Node *lc, *rc;
    };

private:
    
    Node *nodes, *root;
    int node;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) {
            nodes[node] = {0, 0, 0, 0, nb, ne, NULL, NULL};
            return &nodes[node++];
        }
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        nodes[node] = {0, 0, 0, 0, nb, ne, lc, rc};
        return &nodes[node++];
    }

    void update(int x, int y, Node* node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->sum = y;
            node->max_sub = node->max_pref = node->max_suff = y;
            return;
        }
        update(x, y, node->lc);
        update(x, y, node->rc);
        
        node->sum = node->lc->sum + node->rc->sum;
        node->max_pref = max(node->lc->max_pref, node->lc->sum + node->rc->max_pref);
        node->max_suff = max(node->lc->max_suff + node->rc->sum, node->rc->max_suff);
        node->max_sub = max({node->lc->max_sub, node->rc->max_sub, node->lc->max_suff + node->rc->max_pref});
    }

    Node query(int x, int y, Node* node) {
        if (node->nb >= y || node->ne <= x) {
            return {0, 0, 0, 0, node->nb, node->ne, NULL, NULL};
        }
        if (x <= node->nb && node->ne <= y) {
            return *node;
        }

        Node lc = query(x, y, node->lc);
        Node rc = query(x, y, node->rc);

        return {
            lc.sum + rc.sum,
            max({lc.max_sub, rc.max_sub, lc.max_suff + rc.max_pref}),
            max(lc.max_pref, lc.sum + rc.max_pref),
            max(lc.max_suff + rc.sum, rc.max_suff),
            node->nb, node->ne, NULL, NULL
        };
    }

public:

    Node query(int x, int y) {
        return query(x, y, root);
    }

    void update(int x, int y) {
        update(x, y, root);
    }

    MaxTree (int N) {
        nodes = (Node*)malloc(300'000 * sizeof(Node));
        node = 0;
        root = build(0, N);
    }
};

struct Node;

struct LiftInfo {
    Node* dest;
    long long distance;
    int min_dst;
    MaxTree::Node max_dst;
};

struct Node {
    int no, depth;
    vector<LiftInfo> ancestors;
};

vector<arco_t> adj[MAXN];
Node nodes[MAXN];
bool visited[MAXN];

void dfs(vector<int> &path) {
    int node = path.back();
    int depth = path.size() - 1;

    nodes[node].no = node;
    nodes[node].depth = depth;
    for (int i = 1; i < path.size(); i <<= 1) {
        nodes[node].ancestors.push_back({
            &nodes[path[depth - i]], 0, 0, {0, 0, 0, 0, 0, 0, NULL, NULL}
        });
    }

    visited[node] = true;

    for (auto child: adj[node]) {
        if (!visited[child.dest]) {
            path.push_back(child.dest);

            dfs(path);

            path.pop_back();
        }
    }
}

void dfs(vector<int> &path, vector<long long> &distances) {
    int node = path.back();
    int depth = path.size() - 1;

    nodes[node].no = node;
    nodes[node].depth = depth;
    for (int i = 1; i < path.size(); i <<= 1) {
        nodes[node].ancestors.push_back({
            &nodes[path[depth - i]], distances[depth] - distances[depth - i], 0, {0, 0, 0, 0, 0, 0, NULL, NULL}
        });
    }

    visited[node] = true;

    for (auto child: adj[node]) {
        if (!visited[child.dest]) {
            path.push_back(child.dest);
            distances.push_back(distances.back() + child.peso);

            dfs(path, distances);

            path.pop_back();
            distances.pop_back();
        }
    }
}

void dfs(vector<int> &path, MinTree &min_dst) {
    int node = path.back();
    int depth = path.size() - 1;

    nodes[node].no = node;
    nodes[node].depth = depth;
    for (int i = 1; i < path.size(); i <<= 1) {
        nodes[node].ancestors.push_back({
            &nodes[path[depth - i]], 0, min_dst.query(depth + 1 - i, depth + 1), {0, 0, 0, 0, 0, 0, NULL, NULL}
        });
    }

    visited[node] = true;

    for (auto child: adj[node]) {
        if (!visited[child.dest]) {
            path.push_back(child.dest);
            min_dst.update(depth + 1, child.peso);

            dfs(path, min_dst);

            path.pop_back();
        }
    }
}

void dfs(vector<int> &path, MaxTree &max_dst) {
    int node = path.back();
    int depth = path.size() - 1;

    nodes[node].no = node;
    nodes[node].depth = depth;

    for (int i = 1; i < path.size(); i <<= 1) {
        nodes[node].ancestors.push_back({
            &nodes[path[depth - i]], 0, 0, max_dst.query(depth + 1 - i, depth + 1),
        });
    }

    visited[node] = true;

    for (auto child: adj[node]) {
        if (!visited[child.dest]) {
            path.push_back(child.dest);
            max_dst.update(depth + 1, child.peso);

            dfs(path, max_dst);

            path.pop_back();
        }
    }
}

void inizia(int N, int T, int A[], int B[], int C[]) {
    for (int i = 0; i < N - 1; i++) {
        adj[A[i]].push_back({B[i], C[i]});
        adj[B[i]].push_back({A[i], C[i]});
    }
    vector<int> path(1);
    if (T == 0) {
        dfs(path);
    } else if (T == 1) {
        vector<long long> distances(1);
        dfs(path, distances);
    } else if (T == 2) {
        MinTree min_dst(N);
        dfs(path, min_dst);
    } else if (T == 3) {
        MaxTree max_dst(N);
        dfs(path, max_dst);
    }
}

long long distanza1(int u, int v) {
	if (nodes[u].depth < nodes[v].depth)
        swap(u, v);
    
    int dst = 0;
    int i = nodes[u].ancestors.size() - 1;
    while (nodes[u].depth > nodes[v].depth) {
        i = min(i, (int)nodes[u].ancestors.size() - 1);
        while (nodes[u].ancestors[i].dest->depth < nodes[v].depth) i--;

        u = nodes[u].ancestors[i].dest->no;
        dst += 1 << i;
    }

    i = nodes[u].ancestors.size() - 1;
    while (u != v) {
        i = min(i, (int)nodes[u].ancestors.size() - 1);
        while (nodes[u].ancestors[i].dest->no == nodes[v].ancestors[i].dest->no && i) i--;

        u = nodes[u].ancestors[i].dest->no;
        v = nodes[v].ancestors[i].dest->no;
        dst += 2 << i;
    }

    return dst;
}

long long distanza2(int u, int v) {
    if (nodes[u].depth < nodes[v].depth)
        swap(u, v);
    
    long long dst = 0;
    int i = nodes[u].ancestors.size() - 1;
    while (nodes[u].depth > nodes[v].depth) {
        i = min(i, (int)nodes[u].ancestors.size() - 1);
        while (nodes[u].ancestors[i].dest->depth < nodes[v].depth) i--;

        dst += nodes[u].ancestors[i].distance;
        u = nodes[u].ancestors[i].dest->no;
    }

    i = nodes[u].ancestors.size() - 1;
    while (u != v) {
        i = min(i, (int)nodes[u].ancestors.size() - 1);
        while (nodes[u].ancestors[i].dest->no == nodes[v].ancestors[i].dest->no && i) i--;

        dst += nodes[u].ancestors[i].distance + nodes[v].ancestors[i].distance;
        u = nodes[u].ancestors[i].dest->no;
        v = nodes[v].ancestors[i].dest->no;
    }

    return dst;
}

long long minimo(int u, int v) {
	if (nodes[u].depth < nodes[v].depth)
        swap(u, v);
    
    int dst = INT_MAX;
    int i = nodes[u].ancestors.size() - 1;
    while (nodes[u].depth > nodes[v].depth) {
        i = min(i, (int)nodes[u].ancestors.size() - 1);
        while (nodes[u].ancestors[i].dest->depth < nodes[v].depth) i--;

        dst = min(dst, nodes[u].ancestors[i].min_dst);
        u = nodes[u].ancestors[i].dest->no;
    }

    i = nodes[u].ancestors.size() - 1;
    while (u != v) {
        i = min(i, (int)nodes[u].ancestors.size() - 1);
        while (nodes[u].ancestors[i].dest->no == nodes[v].ancestors[i].dest->no && i) i--;

        dst = min({dst, nodes[u].ancestors[i].min_dst, nodes[v].ancestors[i].min_dst});
        u = nodes[u].ancestors[i].dest->no;
        v = nodes[v].ancestors[i].dest->no;
    }

    return dst;
}

long long massimo(int u, int v) {
	if (nodes[u].depth < nodes[v].depth)
        swap(u, v);
    
    MaxTree::Node u_max = {0, 0, 0, 0, 0, 0, NULL, NULL};
    MaxTree::Node v_max = {0, 0, 0, 0, 0, 0, NULL, NULL};
    int i = nodes[u].ancestors.size() - 1;
    while (nodes[u].depth > nodes[v].depth) {
        i = min(i, (int)nodes[u].ancestors.size() - 1);
        while (nodes[u].ancestors[i].dest->depth < nodes[v].depth) i--;

        MaxTree::Node temp = nodes[u].ancestors[i].max_dst;
        u_max.max_sub = max({u_max.max_sub, temp.max_sub, temp.max_suff + u_max.max_pref});
        u_max.max_pref = max(temp.max_pref, temp.sum + u_max.max_pref);
        u_max.sum += temp.sum;

        u = nodes[u].ancestors[i].dest->no;
    }

    i = nodes[u].ancestors.size() - 1;
    while (u != v) {
        i = min(i, (int)nodes[u].ancestors.size() - 1);
        while (nodes[u].ancestors[i].dest->no == nodes[v].ancestors[i].dest->no && i) i--;

        MaxTree::Node temp_u = nodes[u].ancestors[i].max_dst;
        MaxTree::Node temp_v = nodes[v].ancestors[i].max_dst;
        
        u_max.max_sub = max({u_max.max_sub, temp_u.max_sub, temp_u.max_suff + u_max.max_pref});
        u_max.max_pref = max(temp_u.max_pref, temp_u.sum + u_max.max_pref);
        u_max.sum += temp_u.sum;

        v_max.max_sub = max({v_max.max_sub, temp_v.max_sub, temp_v.max_suff + v_max.max_pref});
        v_max.max_pref = max(temp_v.max_pref, temp_v.sum + v_max.max_pref);
        v_max.sum += temp_v.sum;

        u = nodes[u].ancestors[i].dest->no;
        v = nodes[v].ancestors[i].dest->no;
    }

    return max({u_max.max_sub, v_max.max_sub, u_max.max_pref + v_max.max_pref});
}