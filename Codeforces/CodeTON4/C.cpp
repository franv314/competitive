#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, c, d; cin >> n >> c >> d;
        set<int> a;
        
        long long cost = 0;
        
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            if (a.find(x) != a.end()) {
                cost += c;
            } else {
                a.insert(x);
            }
        }

        long long mi = LLONG_MAX;
        int old = 0;
        int dropped = a.size();
        int holes = 0;

        mi = min(mi, dropped * (long long)c + holes * (long long)d + d);

        for (auto x: a) {
            dropped--;
            holes += x - old - 1;
            old = x;

            //cout << dropped << " " << holes << endl;

            mi = min(mi, dropped * (long long)c + holes * (long long)d);
        }
        cout << cost + mi << "\n";
    }
}