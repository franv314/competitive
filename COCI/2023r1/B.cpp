#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    vector<int> c(n);
    for (auto &x: c) cin >> x;
    
    sort(c.begin(), c.end());
    vector<long long> ps(n + 1);
    for (int i = 1; i <= n; i++) {
        ps[i] = ps[i - 1] + c[i - 1];
    }
    
    while (q--) {
        int k, M; cin >> k >> M;
        
        int l = -1e9 - 10, r = k;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            
            int lo = upper_bound(c.begin(), c.end(), m) - c.begin();
            int hi = c.end() - lower_bound(c.begin(), c.end(), 2 * k - m);
                  
            if (lo + hi >= M) r = m;
            else l = m;
        }
        
        int lo = upper_bound(c.begin(), c.end(), l) - c.begin();
        int hi = c.end() - lower_bound(c.begin(), c.end(), 2 * k - l);
        
        int extra = M - lo - hi;
        
        cout << ps[lo] - (ps[n] - ps[n - hi]) + 2LL * hi * k + (long long)r * extra << '\n';
    }
}