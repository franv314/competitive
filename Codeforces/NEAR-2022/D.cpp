#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;

    while (t--) {
        int n; cin >> n;
        vector<int> a, b;
        
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        vector<bool> done(n);
        vector<set<int>> where;
        long long tot = 1;

        for (int i = 0; i < n; i++) {
            if (a[i] == b[i]) {
                if (done[a[i]]) {
                    tot = 0;
                } else {
                    tot = (tot * 3) % MOD;
                }
                done[a[i]] = true;
            } else {
                if (done[a[i]] && done[b[i]]) {
                    tot = 0;
                } else if (done[a[i]]) {
                    done[b[i]] = true;
                    done[a[i]] = true;
                } else if (done[b[i]]) {
                }
            }
        }

        sort(where.begin(), where.end(), [](set<int> a, set<int> b) { return a.size() < b.size(); });

    }
}