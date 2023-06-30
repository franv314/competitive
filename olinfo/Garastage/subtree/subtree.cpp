#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

#define MAXN 1000000
#define _ << " " <<

vector<int> a;
vector<int> beauty;
vector<int> children[MAXN];

struct EnrichedMap {
    int mode, mode_count;
    unordered_map<int, int> m;

    int size() { return m.size(); }

    void merge(EnrichedMap &other) {
        for (auto x: other.m) {
            m[x.first] += x.second;
            if (m[x.first] > mode_count || (m[x.first] == mode_count && x.first < mode)) {
                mode = x.first;
                mode_count = m[x.first];
            }
        }
    }

    EnrichedMap() { }

    EnrichedMap(int n) {
        mode = n;
        mode_count = 1;
        m[n] = 1;
    }
};

EnrichedMap dfs(int node) {
    EnrichedMap this_node(a[node]), child_map;

    for (auto child: children[node]) {
        child_map = dfs(child);
        if (child_map.size() > this_node.size()) {
            swap(this_node, child_map);
        }
        this_node.merge(child_map);
    }
    
    beauty[node] = this_node.mode;

    return this_node;
}

vector<int> solve(int n, vector<int> p, vector<int> a) {
    ::a = a;
    beauty.resize(n);
	for (int i = 1; i < n; i++)
        children[p[i]].push_back(i);

    dfs(0);

    return beauty;
}