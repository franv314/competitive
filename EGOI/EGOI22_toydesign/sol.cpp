#include <bits/stdc++.h>
using namespace std;

int Connected(int a, int i, int j);
void DescribeDesign(vector<pair<int,int>> result);

void ToyDesign(int n, int max_ops) {
    vector<pair<int, int>> versions;
    versions.emplace_back(0, 1);
    
    vector<pair<int, int>> edges;
    
    for (int node = 2; node <= n; node++) {
        int l = 0, r = versions.size() + 1;
        int new_ver;
        while (l + 1 < r) {
            int m = (l + r - 1) / 2;
            auto [version, pin] = versions[m];
            
            int ans = Connected(version, pin, node);
            if (ans == version) {
                r = m + 1;
            } else {
                l = m + 1;
                new_ver = ans;
            }
        }
        
        if (l < versions.size()) {
            edges.emplace_back(node, versions[l].second);
        } else {
            versions.emplace_back(new_ver, node);
        }
    }
    DescribeDesign(edges);
}