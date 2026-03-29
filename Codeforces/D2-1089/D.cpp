#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string a; cin >> a;
    string b; cin >> b;

    vector<int> pa(n + 1), pb(n + 1);
    for (int i = 0; i < n; i++) {
        pa[i + 1] = pa[i] + (a[i] == '(' ? +1 : -1);
        pb[i + 1] = pb[i] + (b[i] == '(' ? +1 : -1);
    }

    vector<int> ca(n / 2), cb(n / 2);
    for (int i = 0; i <= n; i++) {
        if (pa[i] != n / 2) ca[pa[i]]++;
        if (pb[i] != n / 2) cb[pb[i]]++;
    }

    int da = find_if(ca.begin(), ca.end(), [](int x) { return x > 2; }) - ca.begin();
    int db = find_if(cb.begin(), cb.end(), [](int x) { return x > 2; }) - cb.begin();

    if (da != db) return void(cout << "NO\n");

    int cca = 0, ccb = 0;
    for (int i = 0; i < (int)a.size() - 1; i++) {
        cca += (a[i] == '(' && a[i + 1] == ')');
        ccb += (b[i] == '(' && b[i + 1] == ')');
    }

    if (cca == ccb) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
