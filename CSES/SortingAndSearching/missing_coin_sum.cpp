#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    sort(a.begin(), a.end());
    
    long long missing = 1;
    for (auto x: a) {
        if (x > missing) return cout << missing << '\n', 0;
        missing += x;
    }

    cout << accumulate(a.begin(), a.end(), 0ll) + 1 << '\n';
}