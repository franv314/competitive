#include <bits/stdc++.h>
using namespace std;

int t, n;
vector<int> a;

int GCD(vector<int> a) {
    int gcd = __gcd(a[0], a[0]);
    for (int i = 1; i < n; i++)
        gcd = __gcd(gcd, a[i]);
    return gcd;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> t;

    while (t--) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        
        int last = a.back();
        
        if (GCD(a) == 1) {
            cout << "0\n";
            continue;
        }

        a[n - 1] = __gcd(a[n - 1], n);
        if (GCD(a) == 1) {
            cout << "1\n";
            continue;
        }
    
        a[n - 1] = last;
        a[n - 2] = __gcd(a[n - 2], n - 1);
        if (GCD(a) == 1) {
            cout << "2\n";
            continue;
        }

        cout << "3\n";
    }
    return 0;
}