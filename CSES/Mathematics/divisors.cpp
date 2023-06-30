#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int x, i, total = 0; cin >> x;
        for (i = 1; i * i < x; i++)
            if (x % i == 0)
                total += 2;
        cout << total + (i * i == x) << endl;
    }
}