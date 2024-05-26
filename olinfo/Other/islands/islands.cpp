#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N; in >> N;
    vector<pair<int, int>> next(N);
    vector<vector<pair<int, int>>> inv(N);
    for (int i = 0; i < N; i++) {
        int u, w; in >> u >> w;
        next[i] = {u - 1, w};
        inv[u - 1].emplace_back(i, w);
    }

    long long ans = 0;
    vector<int> visited(N);

    auto dfs = [&](auto &&dfs, int node) -> pair<long long, long long> {
        visited[node] = 1;

        long long root_path = 0, internal_path = 0, ma1 = 0, ma2 = 0;

        for (auto [x, w]: inv[node]) {
            if (!visited[x]) {
                auto [root, internal] = dfs(dfs, x);
                root_path = max(root_path, w + root);
                internal_path = max(internal_path, internal);

                if (w + root > ma1) {
                    ma2 = ma1;
                    ma1 = w + root;
                } else if (w + root > ma2) {
                    ma2 = w + root;
                }
            }
        }

        return {root_path, max(internal_path, ma1 + ma2)};
    };

    for (int i = 0; i < N; i++) {
        if (visited[i]) continue;

        int curr;
        deque<int> cycle;
        for (curr = i; !visited[curr]; curr = next[curr].first) {
            cycle.push_back(curr);
            visited[curr] = 1;
        }
        
        while (cycle.front() != curr) {
            visited[cycle.front()] = 0;
            cycle.pop_front();
        }
        
        long long best = 0;
        
        vector<tuple<int, long long, long long>> cycle_values;
        long long tot_dist = 0;

        for (auto x: cycle) {
            auto [root, internal] = dfs(dfs, x);
            best = max(best, internal);

            cycle_values.emplace_back(x, tot_dist, root);
            tot_dist += next[x].second;
        }

        multiset<long long> furthest;
        for (auto [node, dist, len]: cycle_values) {
            furthest.insert(dist + len);
        }

        for (auto [node, dist, len]: cycle_values) {
            furthest.erase(furthest.find(dist + len));
            best = max(best , len + *furthest.rbegin() - dist);
            furthest.insert(dist + len + tot_dist);
        }

        ans += best;
    }

    out << ans << '\n';
}