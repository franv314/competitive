#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    
    multiset<int> a, b;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a.insert(x);
    }
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        b.insert(x);
    }

    map<pair<multiset<int>, multiset<int>>, int> knowns;

    int i;
    for (i = 0; i < k / 2; i++) {
        if (knowns.count({a, b})) {
            break;
        }

        knowns[{a, b}] = i;
        {
            int ma_b = *b.rbegin();
            int mi_a = *a.begin();
            if (ma_b > mi_a) {
                a.erase(a.find(mi_a));
                b.erase(b.find(ma_b));
                a.insert(ma_b);
                b.insert(mi_a);
            }
        }
        {
            int ma_a = *a.rbegin();
            int mi_b = *b.begin();
            if (ma_a > mi_b) {
                b.erase(b.find(mi_b));
                a.erase(a.find(ma_a));
                b.insert(ma_a);
                a.insert(mi_b);
            }
        }
    }
    
    if (i != k / 2) {
        int diff = k / 2 - i;
        int mod = i - knowns[{a, b}];
        int j = diff % mod;

        for (i = 0; i < j; i++) {
            {
                int ma_b = *b.rbegin();
                int mi_a = *a.begin();
                if (ma_b > mi_a) {
                    a.erase(a.find(mi_a));
                    b.erase(b.find(ma_b));
                    a.insert(ma_b);
                    b.insert(mi_a);
                }
            }
            {
                int ma_a = *a.rbegin();
                int mi_b = *b.begin();
                if (ma_a > mi_b) {
                    b.erase(b.find(mi_b));
                    a.erase(a.find(ma_a));
                    b.insert(ma_a);
                    a.insert(mi_b);
                }
            }
        }
    }

    if (k & 1) {
        int ma_b = *b.rbegin();
        int mi_a = *a.begin();
        if (ma_b > mi_a) {
            a.erase(a.find(mi_a));
            b.erase(b.find(ma_b));
            a.insert(ma_b);
            b.insert(mi_a);
        }
    }

    cout << accumulate(a.begin(), a.end(), 0LL) << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}