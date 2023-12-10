#include <bits/stdc++.h>
using namespace std;

int n;

int query(int x) {
    if (x == 0 || x == n + 1) return INT_MAX; 
    
    cout << "? " << x << endl;
    int ans; cin >> ans;
    return ans;
}

int main() {
    cin >> n;

    int l = 1, r = n + 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;

        if (query(m) > query(m - 1)) r = m;
        else l = m;
    }

    cout << "! " << l << endl;
}
