#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int n, s, r; cin >> n >> s >> r;

        cout << s - r << " ";
        
        int lo = r / (n - 1);
        int hi = r % (n - 1);

        int i = 0;
        for (int i = 0; i < hi; i++)
            cout << lo + 1 << " ";
        for (int i = hi; i < n - 1; i++)
            cout << lo << " ";
        cout << "\n";
    }
}