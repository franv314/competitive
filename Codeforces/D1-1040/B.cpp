#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

int invs(int n, vector<int> a) {
    int inv = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            inv += a[i] > a[j];
    
    return inv;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    
    for (int i = n; i >= 1; i--) {
        int cnt_l = 0, idx = -1, cnt_r = 0;
        for (int j = 0; j < n; j++) {
            if (a[j] == i) {
                idx = j;
            } else if (a[j] > i) {
                if (idx == -1)
                    cnt_l++;
                else
                    cnt_r++;
            }
        }
        if (cnt_l > cnt_r) a[idx] = 2 * n - a[idx];
    }
    cout << invs(n, a) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}