#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;

    vector<int> idxs(n * n + 1);
    iota(idxs.begin(), idxs.end(), 1);

    vector<int> count(n * n + 2, n);

    for (int i = 0; i < n; i++) {
        cout << "? " << idxs.size();
        for (auto x: idxs) cout << " " << x; cout << endl;

        int l; cin >> l;
        vector<int> rem_idx(l);
        for (auto &x: rem_idx) cin >> x;

        if (rem_idx.size() > n) {
            rem_idx.resize(n + 1);
            cout << "!";
            for (auto x: rem_idx) cout << " " << x; cout << endl;
            return;
        }

        for (auto x: rem_idx) count[x] = i;
        
        vector<int> nidx;
        for (auto x: idxs)
            if (!binary_search(rem_idx.begin(), rem_idx.end(), x))
                nidx.push_back(x);
        idxs = nidx;
    }

    int curr = n;
    deque<int> ans;
    for (int i = n * n + 1; i > 0; i--) {
        if (count[i] == curr) {
            ans.push_front(i);
            curr--;
        }
    }

    cout << "!";
    for (auto x: ans) cout << " " << x; cout << endl;
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}
