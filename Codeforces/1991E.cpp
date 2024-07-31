#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    auto get_partition = [&]() -> optional<array<vector<int>, 2>> {
        vector<int> parity(n, -1);

        for (int i = 0; i < n; i++) {
            if (parity[i] != -1) continue;
            
            parity[i] = 0;
            queue<int> q;
            q.push(0);

            while (!q.empty()) {
                int node = q.front(); q.pop();

                for (auto x: adj[node]) {
                    if (parity[x] == -1) {
                        parity[x] = !parity[node];
                        q.push(x);
                    } else if (parity[x] == parity[node]) {
                        return {};
                    }
                }
            }
        }

        vector<int> even, odd;
        for (int i = 0; i < n; i++) {
            if (parity[i]) odd.push_back(i + 1);
            else even.push_back(i + 1);
        }

        return {{even, odd}};
    };

    auto alice = [&]() {
        cout << "Alice" << endl;

        for (int i = 0; i < n; i++) {
            cout << "1 2" << endl;
            int trash; cin >> trash >> trash;
        }
    };

    auto bob = [&](vector<int> even, vector<int> odd) {
        cout << "Bob" << endl;

        for (int i = 0; i < n; i++) {
            int a, b; cin >> a >> b;
            
            if (even.empty()) {
                if (a == 2 || b == 2) {
                    cout << odd.back() << " 2" << endl;
                } else {
                    cout << odd.back() << " 3" << endl;
                }
                odd.pop_back();
            } else if (odd.empty()) {
                if (a == 1 || b == 1) {
                    cout << even.back() << " 1" << endl;
                } else {
                    cout << even.back() << " 3" << endl;
                }
                even.pop_back();
            } else {
                if (a == 1 || b == 1) {
                    cout << even.back() << " 1" << endl;
                    even.pop_back();
                } else {
                    cout << odd.back() << " 2" << endl;
                    odd.pop_back();
                }
            }
        }
    };

    auto partition = get_partition();
    if (partition) {
        bob(partition.value()[0], partition.value()[1]);
    } else {
        alice();
    }
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}