#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    multiset<int, greater<int>> l;
    multiset<int> r;
    long long sum_l = 0, sum_r = 0;

    auto adjust = [&]() {
        while (l.size() > r.size() + (k & 1)) {
            sum_l -= *l.begin();
            sum_r += *l.begin();

            r.insert(*l.begin());
            l.erase(l.begin());
        }
        while (l.size() < r.size() + (k & 1)) {
            sum_r -= *r.begin();
            sum_l += *r.begin();

            l.insert(*r.begin());
            r.erase(r.begin());
        }
    };

    auto insert = [&](int val) {
        if (val > *l.begin()) {
            r.insert(val);
            sum_r += val;
        } else {
            l.insert(val);
            sum_l += val;
        }
    };

    auto erase = [&](int val) {
        if (val > *l.begin()) {
            r.erase(r.find(val));
            sum_r -= val;
        } else {
            l.erase(l.find(val));
            sum_l -= val;
        }
    };

    for (int i = 0; i < k; i++) {
        l.insert(a[i]);
        sum_l += a[i];
    }
    adjust();

    cout << (long long)*l.begin() * (k & 1) - sum_l + sum_r << ' ';

    for (int i = k; i < n; i++) {
        insert(a[i]);
        erase(a[i - k]);
        adjust();

        cout << (long long)*l.begin() * (k & 1) - sum_l + sum_r << ' ';
    }

    cout << '\n';
}