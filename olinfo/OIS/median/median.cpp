// O(Nlog^2N) solution

#include <bits/stdc++.h>
using namespace std;

#define MAXN 50'001

struct Edge {
    int u, v, w;
};

class Arr {
    int size;
    vector<unsigned> arr;

public:

    void add(const int &idx) { arr[idx + size]++; } 
    unsigned operator[](const int &idx) { return arr[idx + size]; }

    void make_prefix_sums() {
        for (int i = 1; i <= 2 * size; i++) arr[i] += arr[i - 1];
    }

    Arr(int size) : size(size), arr(2 * size + 1) { }
};

class Tree {
    int size, centroid;
    vector<vector<pair<int, int>>> adj;
    vector<int> parent, subtree_size;
    vector<Tree*> decomposed;

    void get_edges(int node, int came_from, vector<Edge> &edges, int &taken) {
        int me = taken;
        for (auto [child, weight]: adj[node]) {
            if (child != came_from) {
                ++taken;
                edges.push_back({me, taken, weight});
                get_edges(child, node, edges, taken);
            }
        }
    }

    int get_sizes(int node = 0, int came_from = -1, int weight = -1) {
        subtree_size[node] = 1;
        parent[node] = came_from;

        for (auto [child, weight]: adj[node])
            if (child != came_from)
                subtree_size[node] += get_sizes(child, node, weight);
        return subtree_size[node];
    }

    int get_centroid(int node = 0, int came_from = -1) {
        for (auto [child, _]: adj[node])
            if (child != came_from && subtree_size[child] * 2 > size)
                return get_centroid(child, node);
        return node;
    }

    void decompose() {
        get_sizes();
        centroid = get_centroid();

        vector<Edge> edges; int temp;

        int count = 0;
        for (auto [child, _]: adj[centroid]) {
            edges.clear(); temp = 0;
            get_edges(child, centroid, edges, temp);
            decomposed.push_back(new Tree(edges));
        }
    }

    int dfs_d(int median, int node, int came_from, Arr &d, int curr_d) {
    	int ret = curr_d <= 0;
    	d.add(curr_d);
        for (auto [child, weight]: adj[node]) {
            if (child != came_from) {
                int add = weight > median ? 1 : -1;
                ret += dfs_d(median, child, node, d, curr_d + add);
            }
        }
        return ret;
    }

    int dfs_c(int median, int node, int came_from, Arr &d1, Arr &d2, int curr_d) {
        int ret = d1[-curr_d] - d2[-curr_d];
        for (auto [child, weight]: adj[node]) {
            if (child != came_from) {
                int add = weight > median ? 1 : -1;
                ret += dfs_c(median, child, node, d1, d2, curr_d + add);
            }
        }
        return ret;
    }

public:

    int query(int median) {
        Arr d1(size);
        
		int to_centroid = 0;

        for (auto [child, weight]: adj[centroid])
            to_centroid += dfs_d(median, child, centroid, d1, weight > median ? 1 : -1);

		d1.make_prefix_sums();

        int count = 0;
        for (auto [child, weight]: adj[centroid]) {
        	int s = 1 + parent[child] == centroid ? subtree_size[child] : size;
        	Arr d2(s);
            dfs_d(median, child, centroid, d2, weight > median ? 1 : -1);
            d2.make_prefix_sums();
            
            count += dfs_c(median, child, centroid, d1, d2, weight > median ? 1 : -1);
        }

		count /= 2;

        for (auto d: decomposed) count += d->query(median);
        return count + to_centroid;
    }

    Tree(vector<Edge> edges) {
        size = edges.size() + 1;
        adj.resize(size);
        parent.resize(size);
        subtree_size.resize(size);

        for (int i = 0; i < edges.size(); i++) {
            adj[edges[i].u].push_back({edges[i].v, edges[i].w});
            adj[edges[i].v].push_back({edges[i].u, edges[i].w});
        }

        if (size) decompose();
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, K; cin >> N >> K;

    vector<Edge> edges(N - 1);

    for (int i = 0; i < N - 1; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].u--; edges[i].v--;
    }

    sort(edges.begin(), edges.end(), [](Edge a, Edge b){ return a.w < b.w; });
    vector<int> ans(N - 1);

    for (int i = 0; i < N - 1; i++) {
        ans[i]  = edges[i].w;
        edges[i].w = i;
    }

    Tree tree(edges);
    
    int l = 0, r = N - 1;
    while (l < r - 1) {
        int m = (l + r - 1) / 2;
        if (tree.query(m) < K) l = m + 1;
        else r = m + 1;
    }
    cout << ans[l];
}