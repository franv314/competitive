#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'000

int N, M;
vector<tuple<int, int, bool>> adj[MAXN];
long long dst[MAXN];
bool visited[MAXN];

long long dijkstra1() {
    fill(dst, dst + N, 1e18);
    vector<int> came_from(N, -2);

    priority_queue<tuple<long long, int, int>> q;
    q.push({0, 0, -1});
    dst[0] = 0;
    while (!q.empty()) {
        auto [d, node, origin] = q.top(); q.pop();
        if (came_from[node] != -2) continue;

        d *= -1;
        came_from[node] = origin;
        for (auto [n, w, c]: adj[node]) {
            if (d + w < dst[n]) {
                dst[n] = d + w;
                q.push({-dst[n], n, node});
            }
        }
    }

    fill(visited, visited + N, false);
    for (int i = N - 1; i != -1; i = came_from[i])
        visited[i] = true;
    for (int i = 0; i < N; i++) {
        for (auto &[n, w, c]: adj[i]) {
            if (visited[i] && visited[n]) {
                c = false;
            }
        }
    }

    return dst[N - 1];
}

long long dijkstra2(int m) {
    fill(dst, dst + N, 1e18);
    vector<int> ma(N, 0);
    fill(visited, visited + N, false);

    priority_queue<pair<long long, int>> q;
    q.push({0, 0});
    dst[0] = 0;
    while (!q.empty()) {
        auto [d, node] = q.top(); q.pop();
        if (visited[node]) continue;

        d *= -1;
        visited[node] = true;
        for (auto [n, w, c]: adj[node]) {
            int new_max = min(m, max(ma[node], c * (w - 1)));
            long long new_dst = dst[node] + w;
            if (new_dst - new_max < dst[n] - ma[n]) {
                dst[n] = new_dst;
                ma[n] = new_max;
                q.push({-(dst[n] - ma[n]), n});
            }
        }
    }
    return dst[N - 1] - ma[N - 1];
}

long long dijkstra3() {
    fill(dst, dst + N, 1e18);
    fill(visited, visited + N, false);

    priority_queue<tuple<long long, int>> q;
    q.push({0, 0});
    dst[0] = 0;
    while (!q.empty()) {
        auto [d, node] = q.top(); q.pop();
        if (visited[node]) continue;

        d *= -1;
        visited[node] = true;
        for (auto [n, w, c]: adj[node]) {
            if (d + w < dst[n]) {
                dst[n] = d + w;
                q.push({-dst[n], n});
            }
        }
    }

    return dst[N - 1];
}

int fastscan() {
    int ans = 0;
    char c;
    while ((c = getchar_unlocked()) >= '0')
        ans = 10 * ans + c - 48;
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    N = fastscan();
    M = fastscan();
    for (int i = 0; i < M; i++) {
        int A = fastscan(), B = fastscan(), T = fastscan();

        adj[A].push_back({B, T, true});
        adj[B].push_back({A, T, true});
    }

    long long best = dijkstra1();

    if (N <= 2000) {
        long long mi = INT_MAX;
        for (int i = 0; i < N; i++) {
            for (auto &[n, w, c]: adj[i]) {
                if (!c) continue;

                int old_w = w;
                w = 1;
                long long dst = dijkstra3();
                if (dst < best) {
                    mi = min(mi, old_w - best + dst);
                }
                w = old_w;
            }
        }
        if (mi == INT_MAX) mi = -1;
        cout << mi << endl;
        return 0;
    }

    int l = 1, r = 1e9;
    while (l < r + 1) {
        int m = (l + r) / 2;
        if (dijkstra2(m) < best) r = m - 1;
        else l = m + 1;
    }
    if (l > 1e9) l = -1;
    cout << l << endl;
}