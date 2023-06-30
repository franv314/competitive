#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto &x: a) cin >> x;
        
        sort(a.begin(), a.end());
        int curr_target = 1;
        long long type1 = 0;

        for (auto x: a) {
            if (x >= curr_target) {
                type1 += x - curr_target;
                curr_target++;
            }
        }
        cout << type1 << endl;
    }
}