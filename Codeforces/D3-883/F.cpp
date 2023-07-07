#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> freqs(10, 0);
    for (int i = 0; i < n; i++) {
        int t; cin >> t;
        freqs[t]++;
    }
    
    int should_be;
    
    for (;;) {
        cout << "- 0" << endl;
        vector<int> ans(n);
        vector<int> nfreqs(10, 0);
        for (auto &x: ans) {
            cin >> x;
            nfreqs[x]++;
        }
        
        for (int i = 0; i < 10; i++) {
            if (nfreqs[i] > freqs[i]) {
                vector<int> to_be_removed;
                for (int j = 0; j < n; j++) {
                    if (ans[j] != i) to_be_removed.push_back(j + 1);
                }
                n -= to_be_removed.size();
                should_be = i;
                cout << "- " << to_be_removed.size() << " ";
                for (auto x: to_be_removed) cout << x << " ";
                cout << endl;
                goto next;
            }
        }
    }
    
    next:
    for (;;) {
        vector<int> ans(n);
        
        for (auto &x: ans) {
            cin >> x;
        }

        for (int i = 0; i < n; i++) {
            if (ans[i] != should_be) {
                return void(cout << "! " << i + 1 << endl);
            }
        }
        
        cout << "- 0" << endl;
    }
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}