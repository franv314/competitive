#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, Q; cin >> N >> Q;

    vector<pair<int, string>> fragments(Q);
    for (auto &[pos, str]: fragments) {
        int _; cin >> pos >> _ >> str;
    }

    sort(fragments.begin(), fragments.end());

    vector<vector<int>> adj(2 * Q), radj(2 * Q);

    for (int i = 0; i < Q; i++) {
        for (int j = i + 1; j < Q; j++) {
            auto &[pos1, str1] = fragments[i];
            auto &[pos2, str2] = fragments[j];
            if (pos1 + str1.length() <= pos2) break;

            bool dd = true, dr = true, rd = true, rr = true;
            for (int k = pos2 - pos1; k < str1.length(); k++) {
                if (pos1 + k < pos2 + str2.length()) {
                    int idx = pos1 + k - pos2;
                    dd &= str1[k] == str2[idx];
                    dr &= str1[k] == str2[str2.length() - 1 - idx];
                    rd &= str1[str1.length() - 1 - k] == str2[idx];
                    rr &= str1[str1.length() - 1 - k] == str2[str2.length() - 1 - idx];
                }
            }

            if (!dd) {
                adj[2 * i].push_back(2 * j + 1);
                radj[2 * j + 1].push_back(2 * i);
                adj[2 * j].push_back(2 * i + 1);
                radj[2 * i + 1].push_back(2 * j);
            }
            if (!dr) {
                adj[2 * i].push_back(2 * j);
                radj[2 * j].push_back(2 * i);
                adj[2 * j + 1].push_back(2 * i + 1);
                radj[2 * i + 1].push_back(2 * j + 1);
            }
            if (!rd) {
                adj[2 * i + 1].push_back(2 * j + 1);
                radj[2 * j + 1].push_back(2 * i + 1);
                adj[2 * j].push_back(2 * i);
                radj[2 * i].push_back(2 * j);
            }
            if (!rr) {
                adj[2 * i + 1].push_back(2 * j);
                radj[2 * j].push_back(2 * i + 1);
                adj[2 * j + 1].push_back(2 * i);
                radj[2 * i].push_back(2 * j + 1);
            }
        }
    }

    vector<bool> vis(2 * Q);
    vector<int> ord, scc(2 * Q, -1);

    auto dfs1 = [&](auto &&dfs1, int node) -> void {
        vis[node] = true;
        for (auto x: adj[node])
            if (!vis[x])
                dfs1(dfs1, x);
        ord.push_back(node);
    };

    auto dfs2 = [&](auto &&dfs2, int node, int root) -> void {
        scc[node] = root;
        for (auto x: radj[node])
            if (scc[x] == -1)
                dfs2(dfs2, x, root);
    };

    for (int i = 0; i < 2 * Q; i++)
        if (!vis[i])
            dfs1(dfs1, i);
    reverse(ord.begin(), ord.end());
    for (auto i: ord)
        if (scc[i] == -1)
            dfs2(dfs2, i, i);
    
    for (int i = 0; i < Q; i++)
        if (scc[2 * i] == scc[2 * i + 1])
            return cout << "NO\n", 0;

    vector<vector<int>> sadj(2 * Q);
    vector<int> deg(2 * Q);
    for (int i = 0; i < 2 * Q; i++) {
        for (auto j: adj[i]) {
            if (scc[i] != scc[j]) {
                sadj[scc[i]].push_back(scc[j]);
                deg[scc[j]]++;
            }
        }
    }

    queue<int> q;
    for (int i = 0; i < 2 * Q; i++)
        if (deg[i] == 0)
            q.push(i);

    ord.assign(2 * Q, -1);
    int cnt = 0;
    while (!q.empty()) {
        auto x = q.front(); q.pop();
        ord[x] = cnt++;

        for (auto y: sadj[x])
            if (--deg[y] == 0)
                q.push(y);
    }

    string ans(N, 'a');
    for (int i = 0; i < Q; i++) {
        if (ord[scc[2 * i]] < ord[scc[2 * i + 1]]) {
            copy(fragments[i].second.rbegin(), fragments[i].second.rend(), ans.begin() + fragments[i].first);
        } else {
            copy(fragments[i].second.begin(), fragments[i].second.end(), ans.begin() + fragments[i].first);
        }
    }

    cout << "YES\n" << ans << "\n";
}
