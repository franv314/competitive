#include <bits/stdc++.h>
using namespace std;

int paper(int N, int M, int A[], int B[]) {
    for (int i = 0; i < M; i++) {
        A[i]--;
        B[i]--;
    }
    
    vector<vector<int>> in_adj(N), out_adj(N);
    for (int i = 0; i < M; i++) {
        in_adj[B[i]].push_back(A[i]);
        out_adj[A[i]].push_back(B[i]);
    }
    
    
    stack<int> nodes;
    vector<bool> visited(N);
    vector<int> component(N, -1);
    
    function<void(int)> visit = [&](int node) {
        if (visited[node]) return;
        visited[node] = true;
        
        for (auto x: out_adj[node]) {
            visit(x);
        }
        
        nodes.push(node);
    };
    
    function<void(int, int)> assign = [&](int node, int root) {
        if (component[node] != -1) return;
        
        component[node] = root;
        
        for (auto x: in_adj[node]) {
            assign(x, root);
        }
    };
    
    for (int i = 0; i < N; i++) {
        visit(i);
    }
    
    while (!nodes.empty()) {
        int i = nodes.top(); nodes.pop();
        assign(i, i);
    }
    
    vector<int> component_size(N), component_in(N);
    for (int i = 0; i < N; i++) {
        component_size[component[i]]++;
    }
    
    for (int i = 0; i < M; i++) {
        if (component[A[i]] != component[B[i]]) {
            component_in[component[B[i]]]++;
        }
    }
    
    int cnt = 0;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (component_size[i] && !component_in[i]) {
            cnt++;
            ans = component_size[i];
        }
    }
    return cnt == 1 ? ans : 0;
}