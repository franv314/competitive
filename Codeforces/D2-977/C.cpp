#include <bits/stdc++.h>
using namespace std;

class Order {
    vector<int> b, nxt;
    map<int, int> uni;
    vector<optional<map<int, int>::iterator>> pos_of;
    vector<set<int>> val_pos;
    int good;
    int start;

    bool is_ok(map<int, int>::iterator it) {
        if (next(it) == uni.end())
            return true;
        
        return next(it)->second == nxt[it->second];
    }

    void ins(int p, int v) {
        auto it = uni.lower_bound(p);
        if (it != uni.begin()) {
            good -= is_ok(prev(it));
        }

        uni[p] = v;
        pos_of[v] = uni.find(p);

        it = pos_of[v].value();
        good += is_ok(it);
        
        if (it != uni.begin()) {
            good += is_ok(prev(it));
        }
    }

    void rem(int p, int v) {
        auto it = pos_of[v].value();
        
        good -= is_ok(it);
        if (it != uni.begin()) {
            good -= is_ok(prev(it));
        }

        uni.erase(p);
        pos_of[v] = {};

        it = uni.lower_bound(p);
        if (it != uni.begin()) {
            good += is_ok(prev(it));
        }
    }

public:
    bool is_good() { return good == uni.size() && uni.begin()->second == start; }

    void upd(int p, int v) {
        if (val_pos[v].count(p))
            return;

        if (uni.count(p)) {
            int w = uni[p];
            rem(p, w);

            auto new_it = val_pos[w].upper_bound(p);
            if (new_it != val_pos[w].end()) {
                ins(*new_it, w);
            }
        }

        val_pos[b[p]].erase(p);
        b[p] = v;
        val_pos[b[p]].insert(p);

        if (!pos_of[v])
            return ins(p, v);
        
        auto it = pos_of[v].value();
        if (it->first < p)
            return;

        rem(it->first, v);
        ins(p, v);
    }

    Order(int n, int m, const vector<int> &a, const vector<int> &b) :
        good(0), start(a[0]), b(b), nxt(n, -1), pos_of(n), val_pos(n)
    {
        for (int i = 0; i < n - 1; i++)
            nxt[a[i]] = a[i + 1];

        for (int i = 0; i < m; i++) {
            val_pos[b[i]].insert(i);
            if (pos_of[b[i]]) continue;

            ins(i, b[i]);
        }
    }
};

void solve() {
    int n, m, q; cin >> n >> m >> q;
    vector<int> a(n), b(m);
    for (auto &x: a) {
        cin >> x;
        x--;
    }
    for (auto &x: b) {
        cin >> x;
        x--;
    }

    Order order(n, m, a, b);
    cout << (order.is_good() ? "YA\n" : "TIDAK\n");

    while (q--) {
        int s, t; cin >> s >> t;
        s--, t--;

        order.upd(s, t);
        cout << (order.is_good() ? "YA\n" : "TIDAK\n");
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}