// Task "Čokolade"

#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

int n, q, k, m;
vector<int> c;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    c.resize(n);

    for (int i = 0; i < n; i++)
        cin >> c[i];
    
    cin >> k >> m;
    for (auto &e: c) {
        if (e > k) e = 2 * k - e;
    }
    sort(c.begin(), c.end());
    
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + c[i];
    }
    cout << prefix[m] << endl;

    while (--q) {
        cin >> k >> m;
        cout << prefix[m] << endl;
    }

    return 0;
}