#include <bits/stdc++.h>
using namespace std;

int N, Q;

class DSU {
    vector<int> nodes;

public:

    int find(int u) {
        while (nodes[u] >= 0)
            u = nodes[u];
        return u;
    }

    pair<int, int> join(int u, int v) {
        u = find(u), v = find(v);
        if (nodes[u] > nodes[v]) swap(u, v);
        
        int old = nodes[v];

        nodes[u] += nodes[v];
        nodes[v] = u;

        return {v, old};
    }

    void revert(pair<int, int> op) {
        int new_p = nodes[op.first];
        nodes[new_p] -= op.second;
        nodes[op.first] = op.second;
    }

    DSU() {}
    DSU(int N) : nodes(N, -1) { }
};

class Seg1D {
    struct Node {
        vector<pair<int, int>> edges, queries;

        int nb, ne;
        Node *lc, *rc;
    } *nodes, *root;
    int no;
    
    int curr;
    DSU dsu;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) {
            nodes[no] = {{}, {}, nb, ne, NULL, NULL};
            return &nodes[no++];
        }
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        nodes[no] = {{}, {}, nb, ne, lc, rc};
        return &nodes[no++];
    }

    void insert_edge(int l, int r, pair<int, int> edge, Node* node) {
        if (node->nb >= r || node->ne <= l) return;
        if (l <= node->nb && node->ne <= r) {
            node->edges.push_back(edge);
            return;
        }
        insert_edge(l, r, edge, node->lc);
        insert_edge(l, r, edge, node->rc);
    }

    void insert_query(int x, pair<int, int> query, Node* node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->queries.push_back(query);
            return;
        }
        insert_query(x, query, node->lc);
        insert_query(x, query, node->rc);
    }

    void dfs(Node* node) {
        vector<pair<int, int>> revert;

        for (auto [a, b]: node->edges)
            revert.push_back(dsu.join(a, b));
   
        for (auto [a, b]: node->queries) {
            int outfit = dsu.find(1 + (a + curr) % N) == dsu.find(1 + (b + curr) % N);
            cout << outfit << "\n";
            curr += outfit;
        }
        
        if (node->nb + 1 != node->ne) {
            dfs(node->lc);
            dfs(node->rc);
        }
        
        while (!revert.empty()) {
            dsu.revert(revert.back());
            revert.pop_back();
        }
    }

public:

    void insert_edge(int l, int r, pair<int, int> edge) { insert_edge(l, r, edge, root); }
    void insert_query(int x, pair<int, int> query) { insert_query(x, query, root); }

    void dfs() { dfs(root); }

    Seg1D() { }
    Seg1D(int N, int Q) : dsu(N + 1) {
        curr = no = 0;
        nodes = (Node*)malloc(2 * Q * sizeof(Node));
        root = build(0, Q);
    }

};

Seg1D tree;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    tree = Seg1D(N, Q + 1);

    map<pair<int, int>, int> edges;
    int time = 0;
    
    for (int t = 1; t < N; t++) {
        int x, y;
        cin >> x >> y;
        pair<int, int> q = minmax(x, y);
        edges[q] = time;
    }

    for (int t = 0; t < Q; t++) {
        int type, x, y;
        cin >> type >> x >> y;

        pair<int, int> q = minmax(x, y);

        if (type == 1) {
            if (edges.find(q) == edges.end()) {
                edges[q] = time;
            } else {
                tree.insert_edge(edges[q], time, q);
                edges.erase(q);
            }
        } else {
            tree.insert_query(time, q);
            time++;
        }
    }

    for (auto [q, t]: edges)
        tree.insert_edge(t, time, q);

    tree.dfs();
}