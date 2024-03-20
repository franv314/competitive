#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> P(N);
    for (auto &p: P) cin >> p;
    
    int Q; cin >> Q;
    vector<vector<pair<int, int>>> queries(N);
    for (int i = 0; i < Q; i++) {
        int a, b; cin >> a >> b;
        queries[a].emplace_back(b, i);
    }
    
    vector<int> ans(Q, -1);
    vector<int> cycle_pos(N, -1);
    
    for (int i = 0; i < N; i++) {
        if (cycle_pos[i] != -1) continue;
        
        vector<int> cycle;
        for (int curr = i; cycle_pos[curr] == -1; curr = P[curr]) {
            cycle_pos[curr] = cycle.size();
            cycle.push_back(curr);
        }
        
        for (auto x: cycle) {
            for (auto [t, idx]: queries[x]) {
                if (cycle_pos[t] >= 0) {
                	ans[idx] = min(
                        (cycle_pos[t] - cycle_pos[x] + cycle.size()) % cycle.size(),
                        (cycle_pos[x] - cycle_pos[t] + cycle.size()) % cycle.size()
                    );
                }
            }
        }
        
        for (auto x: cycle) {
            cycle_pos[x] = -2;
        }
    }
    
    for (auto x: ans) cout << x << ' '; cout << '\n';
}