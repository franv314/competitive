#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    vector<int> arr;
    
    void add(int x, int diff) {
        for (; x < arr.size(); x += x & -x)
            arr[x] += diff;
    }
    
    int query(int x) {
        int ans = 0;
        for (; x; x -= x & -x)
            ans += arr[x];
        return ans;
    }
    
    Fenwick(int size) : arr(size + 1) { }  
};

int main() {
    int n, q; cin >> n >> q;
    Fenwick fenwick(n);
    unordered_map<int, deque<int>> occurrences;
    vector<int> vals(n + 1);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        vals[i] = x;
        if (occurrences[x].empty()) {
            fenwick.add(i, 1);
        }
        occurrences[x].push_back(i);
    }
    
    unordered_map<int, vector<pair<int, int>>> queries;
    vector<int> ans(q);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        queries[l].push_back({r, i});
    }
    
    for (int l = 1; l <= n; l++) {
        for (auto [r, idx]: queries[l]) {
            ans[idx] = fenwick.query(r);
        }
        fenwick.add(l, -1);
        occurrences[vals[l]].pop_front();
        
        if (!occurrences[vals[l]].empty()) {
            fenwick.add(occurrences[vals[l]].front(), 1);
        }
    }
    
    for (auto a: ans) {
        cout << a << '\n';
    }
}