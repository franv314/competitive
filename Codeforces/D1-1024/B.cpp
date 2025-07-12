#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    list<int> a;
    vector<list<int>::iterator> its(n);
    vector<bool> is_odd(n);
    vector<int> even, odd;
    for (int i = 0; i < n; i++) {
        int v; cin >> v;
        v--;
        a.push_back(v);
        its[v] = prev(a.end());
        is_odd[v] = i % 2;
        if (i % 2) odd.push_back(v);
        else even.push_back(v);
    }

    sort(odd.begin(), odd.end());
    sort(even.begin(), even.end());
    vector<int> order;
    for (int i = 0; i < n / 2; i++) {
        order.push_back(even[i]);
        order.push_back(odd[i]);
    }
    if (n % 2) order.push_back(even.back());
    order.pop_back();
    order.pop_back();
    order.pop_back();

    list<int>::iterator base = a.begin();

    for (int i: order) {
        if (its[i] == base) {
            base = next(base);
            continue;
        }
        if (!is_odd[i]) {
            if (its[i] == prev(a.end())) {
                int prv_val = *prev(its[i]);
                a.erase(prev(its[i]));
                a.erase(its[i]);
                
                its[i] = a.insert(prev(prev(a.end())), i);
                its[prv_val] = a.insert(prev(prev(a.begin())), prv_val);
            }

            int nxt_val = *next(its[i]);
            a.erase(next(its[i]));
            a.erase(its[i]);
            
            its[i] = a.insert(base, i);
            base = its[nxt_val] = a.insert(base, nxt_val);
        } else {
            if (its[i] == prev(a.end())) {
                int prv_val = *prev(its[i]);
                a.erase(prev(its[i]));
                a.erase(its[i]);
                
                its[i] = a.insert(prev(prev(a.end())), i);
                its[prv_val] = a.insert(prev(prev(a.begin())), prv_val);
            }

            int nxt_val = *next(its[i]);
            a.erase(next(its[i]));
            a.erase(its[i]);
            
            its[i] = a.insert(base, i);
            base = its[nxt_val] = a.insert(base, nxt_val);
        }
    }

    for (auto x: a) cout << x + 1 << ' '; cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
