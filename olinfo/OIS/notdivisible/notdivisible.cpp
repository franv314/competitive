#include <bits/stdc++.h>
using namespace std;

#define MAXV 1'000'004
#define MAXN 100'001
#define MAXP 78'499
#define MAXL 18

constexpr int BLOCK = 512;

int N, Q, V[MAXN];
int ancestors[MAXN][MAXL], depth[MAXN], other[2 * MAXN];

vector<int> adj[MAXN];
vector<int> dfs_order, pos_in_dfs(MAXN, -1);

vector<int> is_prime(MAXV, -1);
vector<int> primes(1);

struct Query {
    int start, end, lca, i;
};

struct SegTree {
    int tree[262145];

    void build(int node, int size) {
        tree[node] = size;
        
        if (size > 1) {
            build(node * 2, size / 2);
            build(node * 2 + 1, size / 2);
        }
    }

    void remove(int x) {
        for (x += 131071; x; x /= 2)
            tree[x]--;
    }

    void insert(int x) {
        for (x += 131071; x; x /= 2)
            tree[x]++;
    }

    int find(int node, int size) {
        if (size == 1) return node - 131071;
        if (tree[2 * node]) return find(2 * node, size / 2);
        return find(2 * node + 1, size / 2);
    }

    SegTree() {
        build(1, 131072);
    }
};

void sieve() {
    for (int i = 2; i < MAXV; i++) {
        if (is_prime[i] == 0) continue;
        
        is_prime[i] = primes.size();
        primes.push_back(i);
        
        for (int j = 2 * i; j < MAXV; j += i)
            is_prime[j] = 0;
    }
}

void dfs(int node, vector<int> &path) {
    depth[node] = path.size();

    for (int i = 0; (1 << i) <= path.size(); i++) {
        ancestors[node][i] = path[path.size() - (1 << i)];
    }

    int fst = dfs_order.size();
    pos_in_dfs[node] = fst;
    dfs_order.push_back(V[node]);

    for (auto child: adj[node]) {
        if (pos_in_dfs[child] == -1) {
            path.push_back(node);
            dfs(child, path);
            path.pop_back();
        }
    }

    int lst = dfs_order.size();
    other[fst] = lst, other[lst] = fst;
    dfs_order.push_back(V[node]);
}

int find_lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a, b);

    for (int j = MAXL - 1; j >= 0; j--) {
        if (ancestors[b][j] && depth[ancestors[b][j]] >= depth[a]) {
            b = ancestors[b][j];
        }
    }

    if (a == b) return a;

    for (int j = MAXL - 1; j >= 0; j--) {
        if (ancestors[a][j] && ancestors[a][j] != ancestors[b][j]) {
            a = ancestors[a][j], b = ancestors[b][j];
        }
    }

    return ancestors[a][0];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    sieve();
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> V[i];
        V[i] = is_prime[V[i]];
    }
    for (int i = 1; i < N; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> path;
    dfs(1, path);

    cin >> Q;
    vector<Query> queries(Q);
    vector<int> answers(Q);

    for (int q = 0; q < Q; q++) {
        int a, b; cin >> a >> b;
        
        if (pos_in_dfs[a] > pos_in_dfs[b]) swap(a, b);
        int start = pos_in_dfs[a] + 1, end = pos_in_dfs[b] + 1;

        int lca = find_lca(a, b);

        queries[q] = {start, end, lca, q};
    }

    sort(queries.begin(), queries.end(), [&](Query a, Query b) {
        auto [s1, e1, l1, i1] = a;
        auto [s2, e2, l2, i2] = b;
        if (s1 / BLOCK != s2 / BLOCK) return s1 < s2;
        if ((s1 / BLOCK) % 2) return e2 > e1;
        return e1 < e2;
    });

    bitset<2 * MAXN> curr;
    int amounts[MAXP];
    
    SegTree not_in;

    int curr_l = 0, curr_r = 0;
    for (auto [start, end, lca, i]: queries) {
        while (curr_r < end) {
            int x = dfs_order[curr_r];

            if (x) {
                if (curr[other[curr_r]]) {
                    if (--amounts[x] == 0) not_in.insert(x);
                } else {
                    if (++amounts[x] == 1) not_in.remove(x);
                }
            }

            curr.set(curr_r++);
        }
        while (curr_r > end) {
            curr_r--;
            int x = dfs_order[curr_r];

            if (x) {
                if (curr[other[curr_r]]) {
                    if (++amounts[x] == 1) not_in.remove(x);
                } else {
                    if (--amounts[x] == 0) not_in.insert(x);
                }
            }

            curr.reset(curr_r);
        }
        while (curr_l < start) {
            int x = dfs_order[curr_l];

            if (x) {
                if (curr[other[curr_l]]) {
                    if (++amounts[x] == 1) not_in.remove(x);
                } else {
                    if (--amounts[x] == 0) not_in.insert(x);
                }
            }

            curr.reset(curr_l++);
        }
        while (curr_l > start) {
            curr_l--;
            int x = dfs_order[curr_l];

            if (x) {
                if (curr[other[curr_l]]) {
                    if (--amounts[x] == 0) not_in.insert(x);
                } else {
                    if (++amounts[x] == 1) not_in.remove(x);
                }
            }

            curr.set(curr_l);
        }

        bool added = false;
        int x = dfs_order[pos_in_dfs[lca]];
        if (x && amounts[x] == 0) {
            not_in.remove(x);
            added = true;
        }

        answers[i] = not_in.find(1, 131072);

        if (added) {
            not_in.insert(x);
        }
    }

    for (auto x: answers)
        cout << primes[x] << "\n";
}