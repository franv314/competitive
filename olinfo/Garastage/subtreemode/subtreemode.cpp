#include <bits/stdc++.h>
using namespace std;

#define MAXN 1'000'000

struct Info {
    int mode;
    vector<int> elems;
    vector<int> freq;

    void add_single(int num) {
        elems.push_back(num);

        int old_mode_freq = freq[mode];
        freq[num]++;

        if (freq[num] > old_mode_freq || (freq[num] == old_mode_freq && num < mode)) {
            mode = num;
        }
    }

    void merge(Info *other) {
        for (auto elem: other->elems) {
            add_single(elem);
        }
    } 

    void reset() {
        for (auto elem: elems) {
            freq[elem]--;
        }
        elems.clear();
        mode = 0;
    }

    Info() : freq(MAXN) {}
    Info(int num) : mode(num), freq(MAXN) {
        elems.push_back(num);
        freq[num] = 1;
    }
};

vector<int> solve(int n, vector<int> p, vector<int> a) {
    vector<Info*> pool(20);
    for (auto &info: pool) {
        info = new Info;
    }

    function<Info*()> get_pool = [&]() {
        Info* info = pool.back();
        pool.pop_back();
        return info;
    };

    function<void(Info*)> return_pool = [&](Info *info) {
        info->reset();
        pool.push_back(info);
    };

    vector<vector<int>> children(n);
    vector<int> subtree_size(n);
    vector<int> ans(n);

    for (int i = 1; i < n; i++) {
        children[p[i]].push_back(i);
    }
    
    function<int(int)> get_size = [&](int node) -> int {
        subtree_size[node] = 1;
        for (auto child: children[node]) {
            subtree_size[node] += get_size(child);
        }
        return subtree_size[node];
    };
    get_size(0);

    function<Info*(int)> get_sol = [&](int node) -> Info* {
        if (children[node].empty()) {
            ans[node] = a[node];
            Info *info = get_pool();
            info->add_single(a[node]);
            return info;
        }
        swap(
            children[node].back(),
            *max_element(children[node].begin(), children[node].end(), [&](int a, int b) {
                return subtree_size[a] < subtree_size[b];
            })
        );

        Info *info = get_sol(children[node].back());
        children[node].pop_back();

        info->add_single(a[node]);
        for (auto child: children[node]) {
            Info *child_info = get_sol(child);
            info->merge(child_info);
            return_pool(child_info);
        }

        ans[node] = info->mode;
        return info;
    };
    get_sol(0);
    return ans;
}