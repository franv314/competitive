#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    
    vector<int> found(n + 1, 1);
    
    list<int> decreases;
    for (int i = n - 1; i >= 0; i--) {
        int g = a[i];
        decreases.push_front(i);
        for (auto it = next(decreases.begin()); it != decreases.end(); it++) {
            int ng = gcd(g, a[*it]);
            if (ng == g) {
                it--;
                decreases.erase(next(it));
            } else {
                found[*it - i] = max(found[*it - i], g);
                g = ng;
            }
        }
        found[n - i] = max(found[n - i], g);
    }
    
    for (int i = n - 2; i >= 0; i--) {
        found[i] = max(found[i], found[i + 1]);
    }
    
    for (int i = 1; i <= n; i++) {
        cout << found[i] << ' ';
    }
    cout << '\n';
}

int main() {
	int t; cin >> t;
	while (t--) solve();
}
