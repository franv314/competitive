#include <bits/stdc++.h>
using namespace std;

int64_t query(int l, int r) {
    if (l == r) return 0;
    cout << "? " << l << " " << r << endl;
    int64_t ans; cin >> ans;
    return ans;
}

void solve() {
    int n; cin >> n;
    
    function<int(int, int)> get_max = [&](int l, int r) -> int {
        if (l + 1 == r) return l;
        
        int m = midpoint(l, r);
        int max_l = get_max(l, m);
        int max_r = get_max(m, r);
        
        int64_t query_1 = query(l, max_r - 1);
        int64_t query_2 = query(l, max_r);
        
        if (query_1 == query_2) return max_r;
        else return max_l;
    };
    
    int ans = get_max(1, n + 1);
    cout << "! " << ans << endl;
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}