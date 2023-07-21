#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

struct ProcessInfo {
    long long val;
    gp_hash_table<int, long long> products;
};

long long smaltisci(int N, int M, vector<int> A, vector<vector<int>> B) {
    vector<long long> substances(N);
    vector<ProcessInfo> processes(M);
    
    vector<vector<int>> product_of(N);
    
    std::priority_queue<
        tuple<long long, int, bool>,
        vector<tuple<long long, int, bool>>,
        greater<tuple<long long, int, bool>>
    > q;
    array visited = {vector(N, false), vector(M, false)};
    
    for (int i = 0; i < N; i++) {
        substances[i] = 1e18;
    }
    
    for (int i = 0; i < M; i++) {
        if (B[i].empty()) {
            q.push({0, i, true});
        }
        for (auto b: B[i]) {
            product_of[b].push_back(i);
        }
    }
    
    while (!q.empty()) {
        auto [dst, idx, is_proc] = q.top(); q.pop();
        if (visited[is_proc][idx]) continue;
        visited[is_proc][idx] = true;
        
        if (is_proc) {
            if (substances[A[idx]] > dst + 1) {
                substances[A[idx]] = dst + 1;
                q.push({dst + 1, A[idx], false});
            }
        } else {
            for (auto proc: product_of[idx]) {
                bool improved = false;
                if (processes[proc].products.find(idx) == processes[proc].products.end()) {
                    processes[proc].products[idx] = dst;
                    
                    if (processes[proc].products.size() == B[proc].size()) {
                        for (auto [sub, d]: processes[proc].products) {
                            processes[proc].val += d;
                        }
                        improved = true;
                    }
                } else {
                    long long diff = dst - processes[proc].products[idx];
                    if (diff < 0) {
                        processes[proc].products[idx] = dst;
                        processes[proc].val += diff;
                        improved = true;
                    }
                }
                
                if (improved) {
                    q.push({processes[proc].val, proc, true});
                }
            }
        }
    }
    
    return substances[0];
}