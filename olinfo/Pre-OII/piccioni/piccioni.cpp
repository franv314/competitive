#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'001

constexpr int BLOCK = 2048;

class PS {
    vector<pair<int, int>> freqs;
    vector<tuple<int, int, long long>> pref;

public:

    pair<int, long long> query(int x) {
        int l = 0, r = pref.size();
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (get<0>(pref[m]) > x) r = m;
            else l = m;
        }
        return {get<1>(pref[l]), get<2>(pref[l])};
    }

    PS(PS a, PS b) {
        int pos_a = 0, pos_b = 0;
        while (pos_a < a.freqs.size() - 1 || pos_b < b.freqs.size() - 1) {
            if (a.freqs[pos_a].first < b.freqs[pos_b].first) {
                freqs.push_back(a.freqs[pos_a++]);
            } else if (a.freqs[pos_a].first > b.freqs[pos_b].first) {
                freqs.push_back(b.freqs[pos_b++]);
            } else {
                pair<int, int> temp = {a.freqs[pos_a].first, a.freqs[pos_a].second + b.freqs[pos_b].second};
                freqs.push_back(temp);
                pos_a++, pos_b++;
            }
        }

        pref.push_back({INT_MIN, 0, 0});
        int cnt = 0;
        long long acc = 0;
        for (auto [val, freq]: freqs) {
            acc += val * (long long)freq;
            cnt += freq;
            pref.push_back({val, cnt, acc});
        }

        freqs.push_back({INT_MAX, 0});
    }

    PS(int a) {
        freqs.push_back({a, 1});
        freqs.push_back({INT_MAX, 0});

        pref.push_back({INT_MIN, 0, 0});
        pref.push_back({a, 1, a});
    }
};

class SegTree {
    struct Node {
        PS val;
        int nb, ne;

        Node *lc, *rc;

        Node(int nb, int ne, int val) :
            val(val), nb(nb), ne(ne), lc(NULL), rc(NULL) { }
        
        Node(int nb, int ne, Node *lc, Node *rc) :
            val(lc->val, rc->val), nb(nb), ne(ne), lc(lc), rc(rc) { }
    } *root;

    Node *build(int nb, int ne, int arr[]) {
        if (nb + 1 == ne) return new Node(nb, ne, arr[nb]);
        Node *lc = build(nb, (nb + ne) / 2, arr);
        Node *rc = build((nb + ne) / 2, ne, arr);
        return new Node(nb, ne, lc, rc);
    }

    void update(int arr[], Node *node) {
        if (node->nb + 1 == node->ne) {
            node->val = PS(arr[node->nb]);
            return;
        }
        update(arr, node->lc);
        update(arr, node->rc);
        node->val = PS(node->lc->val, node->rc->val);
    }

    pair<int, long long> query(int l, int r, int x, Node *node) {
        if (node->nb >= r || node->ne <= l) return {0, 0};
        if (l <= node->nb && node->ne <= r) return node->val.query(x);
        auto [c1, s1] = query(l, r, x, node->lc);
        auto [c2, s2] = query(l, r, x, node->rc);
        return {c1 + c2, s1 + s2};
    }

public:

    pair<int, long long> query(int l, int r, int x) { return query(l, r, x, root); }
    void update(vector<int> arr) { update(arr.data(), root); }
    SegTree(vector<int> arr) { root = build(0, arr.size(), arr.data()); }
};

set<int> children[MAXN];
int *K;

int depth[MAXN];
pair<int, int> subtree[MAXN];
vector<int> dfs_order;

void dfs(int node, int depth = 0) {
    subtree[node].first = dfs_order.size();
    dfs_order.push_back(depth);

    ::depth[node] = depth;

    for (auto child: children[node]) {
        dfs(child, depth + 1);
    }
    subtree[node].second = dfs_order.size();
}

void calcola_disagio(int N, int Q, int P[], int K[], int u[], int v[], long long risposta[]) {
    ::K = K;
	for (int i = 2; i <= N; i++)
        children[P[i]].insert(i);
    dfs(1);

    map<int, pair<int, int>> buffer;

    SegTree segtree(dfs_order);
    int a = 0;
    for (int i = 0; i < Q; i++) {
        if (v[i] == -1) {
            if (buffer.find(u[i]) != buffer.end()) {
                int d = buffer[u[i]].second;
                long long ans = 0;
                stack<int> q;
                q.push(u[i]);
                while (!q.empty()) {
                    int curr = q.top(); q.pop();
                    if (curr != u[i])
                        ans += max(0, K[u[i]] + d + 1 - buffer[curr].second);
                    for (auto child: children[curr])
                        q.push(child);
                }
                risposta[a++] = ans;
            } else {
                auto [l, r] = subtree[u[i]];
                auto [c, s] = segtree.query(l + 1, r, K[u[i]] + depth[u[i]]);
                long long ans = (long long)(K[u[i]] + depth[u[i]] + 1) * c - s;
                
                for (auto [piccione, pos]: buffer) {
                    auto [link, d] = pos;
                    if (l <= subtree[piccione].first && subtree[piccione].first < r)
                        ans -= max(0, K[u[i]] + depth[u[i]] + 1 - depth[piccione]);
                    if (l <= subtree[link].first && subtree[link].first < r)
                        ans += max(0, K[u[i]] + depth[u[i]] + 1 - d);
                }
                risposta[a++] = ans;
            }
        } else {
            if (buffer.find(v[i]) != buffer.end())
                buffer[u[i]] = {buffer[v[i]].first, buffer[v[i]].second + 1};
            else
                buffer[u[i]] = {v[i], depth[v[i]] + 1};

            children[P[u[i]]].erase(u[i]);
            children[v[i]].insert(u[i]);
            P[u[i]] = v[i];

            if (buffer.size() > BLOCK) {
                buffer.clear();
                dfs_order.clear();
                dfs(1);
                segtree.update(dfs_order);
            }
        }
    }
}