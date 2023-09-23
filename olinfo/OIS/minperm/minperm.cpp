#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M; cin >> N >> M;
    vector<int> P(N), L(M);

    for (auto &p: P) cin >> p;
    for (auto &l: L) cin >> l;

    vector<vector<int>> adj(N);
    for (auto l: L) {
        for (int i = 0; i < N - l; i++) {
            adj[i].push_back(i + l);
            adj[i + l].push_back(i);
        }
    }

    vector<bool> cc(N);
    for (int i = 0; i < N; i++) {
        if (cc[i]) continue;

        queue<int> q;
        vector<int> component;
        q.push(i);
        while (!q.empty()) {
            int n = q.front(); q.pop();
            if (cc[n]) continue;
            cc[n] = true;
            component.push_back(n);

            for (auto x: adj[n]) {
                q.push(x);
            }
        }

        sort(component.begin(), component.end());

        for (int i = 0; i < component.size(); i++) {
            for (int j = component.size() - 1; j > i; j--) {
                if (P[component[i]] > P[component[j]]) {
                    swap(P[component[i]], P[component[j]]);
                }
            }
        }
    }    

    for (auto p: P) cout << p << " ";
}