#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

#define MAXV 30'001

struct IteratorWrapper {
    list<pair<int, IteratorWrapper>>::iterator it;

    IteratorWrapper(int i) {}
    IteratorWrapper(list<pair<int, IteratorWrapper>>::iterator it) : it(it) {}
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;

    vector<int> V(N);
    for (auto &v: V) cin >> v;

    vector<list<pair<int, IteratorWrapper>>> adj(N);

    for (int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        
        adj[a].emplace_front(b, 0);
        adj[b].emplace_front(a, 0);

        adj[b].front().second = IteratorWrapper(adj[a].begin());
        adj[a].front().second = IteratorWrapper(adj[b].begin());
    }

    vector<vector<int>> primes(MAXV), prime_sets(MAXV);
    for (int i = 2; i < MAXV; i++) {
        if (primes[i].empty()) {
            for (int j = i; j < MAXV; j += i) {
                primes[j].push_back(i);
            }
        }
    }
    
    for (int i = 2; i < MAXV; i++) {
        int p_no = primes[i].size();
        for (int mask = 1; mask < (1 << p_no); mask++) {
            int val = 1;
            for (int j = 0; j < p_no; j++) {
                if (mask & (1 << j))  {
                    val *= primes[i][j];
                }
            }
            if (__builtin_popcount(mask) & 1) {
                prime_sets[i].push_back(val);
            } else {
                prime_sets[i].push_back(-val);
            } 
        }
    }

    vector<int> size(N);
    function<int(int, int)> preprocess = [&](int node, int par) -> int {
        size[node] = 1;
        for (auto [c, _]: adj[node]) {
            if (c != par) {
                size[node] += preprocess(c, node);
            }
        }
        return size[node];
    };

    function<int64_t(int)> centroid_decomposition = [&](int node) -> int64_t {
        int tot_size = preprocess(node, -1);

        int centroid = node, old = -1;
        again:
        for (auto [n, _]: adj[centroid]) {
            if (n != old && size[n] * 2 >= tot_size) {
                old = centroid;
                centroid = n;
                goto again;
            }
        }

        gp_hash_table<int, pair<int64_t, int>> depths;
        int64_t partial = 0;

        for (auto p: prime_sets[V[centroid]]) {
            pair<int64_t, int> &mref = depths[abs(p)];
            mref.first += V[centroid];
            mref.second++;
        }

        for (auto [n, _]: adj[centroid]) {
            stack<tuple<int, int, int64_t>> q;
            vector<pair<int, int64_t>> nodes;

            q.emplace(n, centroid, V[n]);
            while (!q.empty()) {
                auto [nn, par, d] = q.top(); q.pop();
                nodes.emplace_back(nn, d);
                for (auto [c, _]: adj[nn]) {
                    if (c == par) continue;
                    q.emplace(c, nn, d + V[c]);
                }
            }

            for (auto [nn, d]: nodes) {
                for (auto p: prime_sets[V[nn]]) {
                    pair<int64_t, int> &mref = depths[abs(p)];
                    if (p < 0) partial -= (mref.first + d * mref.second);
                    else partial += (mref.first + d * mref.second);
                }
            }

            for (auto [nn, d]: nodes) {
                for (auto p: prime_sets[V[nn]]) {
                    pair<int64_t, int> &mref = depths[abs(p)];
                    mref.first += d + V[centroid];
                    mref.second++;
                }
            }
        }

        vector<int> subtrees;
        for (auto [n, it]: adj[centroid]) {
            subtrees.push_back(n);
            
            adj[n].erase(it.it);
        }
        adj[centroid].clear();

        for (auto n: subtrees) {
            partial += centroid_decomposition(n);
        }

        return partial;
    };

    cout << centroid_decomposition(0) << '\n';
}