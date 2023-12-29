#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    auto check = [&](long long m) {
        for (auto x: a) {
            if (x > m) {
                return false;
            }
        }

        int cnt = 1;
        long long curr = 0;
        for (auto x: a) {
            if (curr + x > m) {
                cnt++;
                curr = 0;
            }
            curr += x;
        }

        return cnt <= k;
    };
    
    long long l = -1, r = 1e18;
    while (l + 1 < r) {
        long long m = l + (r - l) / 2;

        if (check(m)) r = m;
        else l = m;
    }
    
    cout << r << '\n';
}