#include <bits/stdc++.h>
using namespace std;

int t, n, q;
pair<int, int> Q;
vector<int> a;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> t;

    while (t--) {
        cin >> n >> q;
        a.resize(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];

        for (int i = 0; i < q; i++)
            cin >> Q.first >> Q.second;

        int sum = 0, x = 0;
        for (auto y: a) {
            sum += y;
            x ^= y;
        }
        int max_val = sum - x;
        
        pair<int, int> curr_opt = {0, n};

        int pos_b = 0;
        int sum2 = 0, x2 = 0;
        for (int pos_a = 0; pos_a < n; pos_a++) {
            sum2 += a[pos_a];
            x2 ^= a[pos_a];
            while (sum2 - x2 < max_val && pos_b < n) {
                sum2 += a[pos_b];
                x2 ^= a[pos_b];
                pos_b++;
            }
            cout << pos_a << " " << pos_b << " " << sum2 << " " << x2 << endl;
            if (pos_b == n) break;
            if (pos_b - pos_a < curr_opt.second - curr_opt.first) {
                curr_opt = {pos_a, pos_b};
            }

            sum2 -= a[pos_a];
            x2 ^= a[pos_a];
        }
        cout << curr_opt.first + 1 << " " << curr_opt.second + 1 << endl;
    }

    return 0;
}