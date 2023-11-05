#include <bits/stdc++.h>
using namespace std;

typedef double f80;

int N;
vector<f80> P, S, D;
vector<int> R;
vector<vector<int>> adj;

struct Component {
    vector<int> cycle;
    f80 cycle_val;

    bool dfs(f80 k, int node, int depth, f80 max_so_far) {
        max_so_far += D[R[node]] + (k - 1) * P[node];

        if (max_so_far >= 0.0) return true;

        for (auto x: adj[node]) {
            if (dfs(k, x, depth + 1, max(max_so_far, (k - 1) * P[node]))) return true;
        }

        return false;
    }

    bool check(f80 k) {
        if (cycle_val <= k) return true;

        vector<f80> base(cycle.size());
        base[0] = (k - 1) * P[cycle[0]];
        for (int z = 1; z < cycle.size(); z++) {
            base[z] = base[z - 1] + k * P[cycle[z]] - S[cycle[z]];
        }

        deque<pair<f80, int>> max_q;
        for (int z = cycle.size() - 1; z >= 0; z--) {
            while (!max_q.empty() && max_q.back().first < base[z]) max_q.pop_back();
            max_q.emplace_back(base[z], cycle.size() - z);
        }

        f80 n_max = -INFINITY;
        f80 lazy = 0.0;
        for (int z = 0; z < cycle.size(); z++) {
            while (!max_q.empty() && max_q.front().second <= z) max_q.pop_front();
            f80 best = max(max_q.empty() ? -INFINITY : max_q.front().first, n_max) + lazy;

            if (best >= 0.0) return true;

            int s = (cycle.size() - z) % cycle.size();

            for (auto x: adj[cycle[s]]) {
                if (x != cycle[(s - 1 + cycle.size()) % cycle.size()])
                    if (dfs(k, x, cycle.size(), best))
                        return true;
            }

            if (z != cycle.size() - 1) {
                int ch = cycle.size() - z - 1;
                lazy += (k - 1) * P[cycle[ch]] + D[R[cycle[ch]]];

                n_max = max(n_max, (k - 1) * P[cycle[ch]] - lazy);
            }
        }

        return false;
    }

    Component(vector<int> &&cycle) : cycle(cycle) {
        f80 D = 0.0, T = 0.0;
        for (auto x: cycle) {
            D += S[x];
            T += P[x];
        }
        cycle_val = D / T;
    }
};

vector<Component> get_components() {
    vector<Component> components;

    vector<int> visited(N, -2);
    for (int i = 0; i < N; i++) {
        if (visited[i] == -1) continue;
        int curr = i;
        vector<int> cycle;
        for (int z = 0; visited[curr] == -2; curr = R[curr], z++) {
            visited[curr] = z;
            cycle.push_back(curr);
        }

        int off = visited[curr];

        queue<int> q;
        q.push(cycle.back());
        while (!q.empty()) {
            int n = q.front(); q.pop();
            visited[n] = -1;

            for (auto x: adj[n]) {
                if (visited[x] != -1) {
                    q.push(x);
                }
            }
        }

        components.emplace_back(vector<int>(cycle.begin() + off, cycle.end()));
    }

    return components;
}

f80 solve() {
    D.resize(N);
    adj.resize(N);
    for (int i = 0; i < N; i++) {
        D[i] = P[i] - S[i];
        adj[R[i]].push_back(i);
    }
    
    vector<Component> components = get_components();

    f80 l = 0.0, r = 1.0;
    for (int _ = 0; _ < 26; _++) {
        f80 m = (l + r) / 2;

        bool ok = false;
        for (auto &component: components) {
            if (component.check(m)) {
                ok = true;
                break;
            }
        }

        if (ok) r = m;
        else l = m;
    }

    return 100 * (1 - (l + r) / 2);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    P.resize(N);
    S.resize(N);
    R.resize(N);

    for (int i = 0; i < N; i++) cin >> P[i] >> S[i] >> R[i];
 
    cout << setprecision(10) << solve() << '\n';
}