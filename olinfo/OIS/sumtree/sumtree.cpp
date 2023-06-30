#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'001
#define MAXV 30'001

int N, V[MAXN];
vector<int> adj[MAXN];

int sign[MAXV];
vector<int> checks[MAXV];

void init() {
    vector<int> primes[MAXV];
    for (int i = 2; i < MAXV; i++) {
        if (primes[i].empty()) {
            for (int j = i; j < MAXV; j += i) {
                primes[j].push_back(i);
            }
        }
        sign[i] = primes[i].size() & 1 ? 1 : -1;
    }

    for (int i = 2; i < MAXV; i++) {
        int no = primes[i].size();
        for (int mask = 1; mask < (1 << no); mask++) {
            int acc = 1;
            for (int j = 0; j < no; j++) {
                if (mask & (1 << j)) {
                    acc *= primes[i][j];
                }
            }
            checks[i].push_back(acc);
        }
    }
}

class SubtreeInfo {
    int node;
    unordered_map<int, long long> dst;
    unordered_map<int, int> cnt;
    unordered_map<int, long long> nodes;
    long long partial_ans;

public:

    void merge(SubtreeInfo other) {
        partial_ans += other.partial_ans;

        for (auto [node, distance]: other.nodes) {
            long long s = 0;
            int c = 0;
            for (auto check: checks[V[node]]) {
                s += dst[check] * sign[check];
                c += cnt[check] * sign[check];
            }
            partial_ans += s + c * distance;
        }
        
        for (auto [node, distance]: other.nodes) {
            nodes[node] = distance + V[this->node];
            for (auto check: checks[V[node]]) {
                dst[check] += distance + V[this->node];
                cnt[check]++;
            }
        }
    }

    long long get_ans() { return partial_ans; }

    SubtreeInfo(int node) : node(node), nodes(), partial_ans(0) {
        nodes[node] = V[node];
        for (auto check: checks[V[node]]) {
            dst[check] += V[node];
            cnt[check]++;
        }
    }
};

SubtreeInfo dfs(int node, int came_from = 0) {
    SubtreeInfo ret(node);

    for (auto child: adj[node]) {
        if (child == came_from) continue;

        SubtreeInfo merge = dfs(child, node);
        ret.merge(merge);
    }
    return ret;
}

int main() {
    init();
    
    cin >> N;
    
    for (int i = 1; i <= N; i++)
        cin >> V[i];
    
    for (int i = 1; i < N; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << dfs(1).get_ans();
}