#include <bits/stdc++.h>
using namespace std;

template<int len = 1>
int64_t solve(int size, vector<int> weights, vector<int> count) {
    if (len - 1 < size) {
        return solve<min(len * 2, 2'000'000)>(size, weights, count);
    }

    bitset<len> found;
    found.set(0);
    for (auto w: weights) {
        for (int t = 0; (1 << t) <= count[w]; t++) {
            found |= found << (w << t);
            count[w] -= (1 << t);
        }
        found |= found << (w * count[w]);
    }

    for (int dec = size / 2, inc = (size + 1) / 2;; dec--, inc++) {
        if (found[dec] || found[inc]) {
            return (int64_t)dec * (size - dec);
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;

    vector<int> p(n);
    vector<vector<int>> adj(n);
    vector<int> children(n), sizes(n);

    for (int i = 1; i < n; i++) {
        cin >> p[i];
        adj[--p[i]].push_back(i);
    }

    stack<int> nodes;
    for (int i = 0; i < n; i++) {
        if (adj[i].empty()) {
            nodes.push(i);
        }
    }

    int64_t ans = 0;

    while (!nodes.empty()) {
        int node = nodes.top(); nodes.pop();
        int size = 0, ma = 0;
        
        for (auto child: adj[node]) {
            size += sizes[child];
            ma = max(ma, sizes[child]);
        }
        
        if (ma * 2 >= size) {
            ans += (int64_t)ma * (size - ma);
        } else {
            vector<int> count(size +1), weights;
            for (auto child: adj[node]) {
                if (count[sizes[child]]++ == 0) {
                    weights.push_back(sizes[child]);
                }
            }

            ans += solve(size, weights, count);
        }

        sizes[node] = size + 1;
        if (node != 0) {
            if (++children[p[node]] == adj[p[node]].size()) {
                nodes.push(p[node]);
            }
        }
    }
    cout << ans << '\n';
}