#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'000

vector<int> children[MAXN];
optional<pair<int, int>> juice[MAXN];

struct Map {
    map<int, long long> vals;

    void merge(Map other) {
        for (auto [day, juice]: other.vals)
            vals[day] += juice;
    }

    void insert_fruit(pair<int, int> fruit) {
        auto [day, juice] = fruit;
        vals[day] += juice;
        long long total = vals[day];
        
        long long added = 0;
        auto it = next(vals.find(day));
        while (it != vals.end() && added + it->second < juice) {
            added += it->second;
            it++;
            vals.erase(prev(it));
        }

        if (it != vals.end()) {
            it->second += added - juice;
        }
    }
};

Map dfs(int node) {
    Map ans;

    for (auto child: children[node]) {
        Map child_values = dfs(child);
        if (child_values.vals.size() > ans.vals.size()) swap(ans, child_values);
        ans.merge(child_values);
    }

    if (juice[node]) {
        ans.insert_fruit(juice[node].value());
    }

    return ans;
}

long long harvest(int n, int m, int k, vector<int> &p, vector<int> &v, vector<int> &d, vector<int> &w) {
    for (int i = 1; i < n; i++)
        children[p[i]].push_back(i);

    for (int i = 0; i < m; i++)
        juice[v[i]] = {d[i], w[i]};

    Map ans = dfs(0);
    long long ret = 0;
    for (auto [_, juice]: ans.vals)
        ret += juice;
    return ret;
}