#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    
    vector<int> a(n), pos_of(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos_of[--a[i]] = i;

    }

    set<int> ones;    
    for (int i = 0; i < n; i++)
        if ((a[i] - a[(i - 1 + n) % n] + n) % n == 1)
            ones.insert(i);

    while (q--) {
        int _x, _y; cin >> _x >> _y;
        _x--, _y--;
        int x = pos_of[_x], y = pos_of[_y];
        swap(pos_of[_x], pos_of[_y]);
        swap(a[x], a[y]);

        if ((a[x] - a[(x - 1 + n) % n] + n) % n == 1) ones.insert(x);
        else ones.erase(x);

        if ((a[y] - a[(y - 1 + n) % n] + n) % n == 1) ones.insert(y);
        else ones.erase(y);

        if ((a[(x + 1) % n] - a[x] + n) % n == 1) ones.insert((x + 1) % n);
        else ones.erase((x + 1) % n);

        if ((a[(y + 1) % n] - a[y] + n) % n == 1) ones.insert((y + 1) % n);
        else ones.erase((y + 1) % n);

        if (ones.size() == n) cout << "DA\n";
        else cout << "NE\n";
    }
}