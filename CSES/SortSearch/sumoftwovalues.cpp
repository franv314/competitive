#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x; cin >> n >> x;
    map<int, int> vals;

    for (int i = 1; i <= n; i++) {
        int v; cin >> v;
        if (vals.count(x - v)) {
            cout << i << ' ' << vals[x - v] << '\n';
            return 0;
        }
        vals[v] = i;
    }
    cout << "IMPOSSIBLE\n";
}