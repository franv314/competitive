#include "Azer.h"
#include <bits/stdc++.h>
using namespace std;

namespace {

// Graph state
int N;
vector<vector<pair<int, int>>> adj;
vector<bool> vis;
vector<int> dst;

// Receive state
int relaxed;
int last_dst;
int curr_number;
int curr_call;
bool expecting_node;

// Helpers
tuple<int, int, int> get_best() {
    int last_best = 0;
    pair<int, int> new_best = {1e9, -1};

    for (int i = 0; i < N; i++) {
        if (vis[i])
            last_best = max(last_best, dst[i]);
        else
            new_best = min(new_best, {dst[i], i});
    }

    return {new_best.second, new_best.first - last_best, last_best};
}


void relax(int node) {
    relaxed++;
    vis[node] = true;
    for (auto [v, w]: adj[node])
        dst[v] = min(dst[v], dst[node] + w);
}

void send_dst(int dst) {
    if (relaxed == N)
        return;

    expecting_node = false;
    curr_call = 0;
    curr_number = 0;

    dst = min(dst, 511);

    for (int i = 0; i < 9; i++)
        SendA((dst >> i) & 1);
}

void send_node(int node) {
    for (int i = 0; i < 11; i++)
        SendA((node >> i) & 1);
}

}

void InitA(int N, int A, vector<int> U, vector<int> V, vector<int> C) {
    ::N = N;
    adj.resize(N);
    vis.resize(N);
    dst.resize(N, 1e9);
    dst[0] = 0;

    for (int i = 0; i < A; i++) {
        adj[U[i]].emplace_back(V[i], C[i]);
        adj[V[i]].emplace_back(U[i], C[i]);
    }

    auto [node, dist, _] = get_best();
    send_dst(dist);
}

void ReceiveA(bool x) {
    int expecting = expecting_node ? 11 : 9;

    curr_number |= (x << curr_call);
    
    if (++curr_call == expecting) {
        if (expecting_node) {
            auto [node, dist, last_best] = get_best();
            dst[curr_number] = last_best + last_dst;
            relax(curr_number);

            tie(node, dist, last_best) = get_best();
            send_dst(dist);
        } else {
            last_dst = curr_number;
            auto [node, dist, _] = get_best();
            if (curr_number < dist) {
                expecting_node = true;
                curr_call = 0;
                curr_number = 0;
            } else {
                send_node(node);
                relax(node);
                auto [node, dist, _] = get_best();
                send_dst(dist);
            }
        }
    }
}

vector<int> Answer() {
    return dst;
}
