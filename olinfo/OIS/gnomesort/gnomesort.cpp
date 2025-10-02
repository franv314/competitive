#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    vector<int> A(N);
    for (auto &x: A) cin >> x;

    vector<bool> vis(N);
    vector<pair<int, int>> pairs;

    for (int i = 0; i < N; i++) {
        if (vis[i]) continue;
        vector<int> pos = {i};
        for (int c = A[i]; c != i; c = A[c])
            pos.push_back(c);
    
        sort(pos.begin(), pos.end());
        for (auto x: pos) vis[x] = true;

        if (!is_sorted(pos.begin(), pos.end(), [&](int u, int v) { return A[u] > A[v]; }))
            return cout << "NO\n", 0;
        
        if (pos.size() == 2)
            pairs.emplace_back(pos[0], pos[1]);
    }

    sort(pairs.begin(), pairs.end());

    map<int, vector<int>*> lis;
    for (auto [a, b]: pairs) {
        lis[b] = nullptr;
        auto it = lis.find(b);
        if (next(it) != lis.end()) {
            vector<int> *group = next(it)->second;
            group->push_back(a);
            group->push_back(b);
            it->second = group;
            lis.erase(next(it));
        } else {
            vector<int> *group = new vector<int>;
            group->push_back(a);
            group->push_back(b);
            it->second = group;
        }
    }

    cout << "YES\n" << lis.size() << '\n';
    for (auto [_, els]: lis) {
        cout << els->size();
        for (auto x: *els)
            cout << " " << x;
        cout << "\n";
        delete els;
    }
}