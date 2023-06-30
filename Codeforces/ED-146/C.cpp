#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, s1, s2; cin >> n >> s1 >> s2;
    vector<pair<int, int>> a(n);
    
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[i - 1] = {x, i};
    }
    sort(a.rbegin(), a.rend());

    vector<int> A, B;
    long long curr_on_a = 0, curr_on_b = 0;
    for (auto [x, i]: a) {
        if ((curr_on_a + 1) * s1 < (curr_on_b + 1) * s2) {
            curr_on_a++;
            A.push_back(i);
        } else {
            curr_on_b++;
            B.push_back(i);
        }
    }
    cout << A.size() << " "; for (auto x: A) cout << x << " "; cout << endl;
    cout << B.size() << " "; for (auto x: B) cout << x << " "; cout << endl;
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}