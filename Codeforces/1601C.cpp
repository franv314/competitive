#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    sort(b.begin(), b.end());
    vector<int> inversions(n + 1);
    
    list<int> vals;
    vector<list<int>::iterator> a_elems;

    for (int i = 0; i < n; i++) {
        vals.push_back(a[i]);
    }
    for (auto it = vals.begin(); it != vals.end(); it++) {
        a_elems.push_back(it);
    }
    a_elems.push_back(vals.end());

    function<void(int, int, int, int)> rec = [&](int la, int ra, int lb, int rb) {
        if (lb == rb) return;
        int mb = (lb + rb) / 2;

        inversions[la] = 0;
        for (int i = la; i < ra - 1; i++) {
            inversions[i + 1] = inversions[i] + (a[i] > b[mb]);
        }
        pair<int, int> best = {inversions[ra - 1], ra - 1};
        inversions[ra - 1] = 0;
        for (int i = ra - 2; i >= la; i--) {
            best = min(best, {inversions[i] + inversions[i + 1] + (a[i] < b[mb]), i});
            inversions[i] = inversions[i + 1] + (a[i] < b[mb]);
        }

        rec(la, best.second + 1, lb, mb);
        vals.insert(a_elems[best.second], b[mb]);
        rec(best.second, ra, mb + 1, rb);
    };

    rec(0, n + 1, 0, m);

    tree<int, null_type, greater_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ord_set;

    long long inv = 0;
    for (auto x: vals) {
        inv += ord_set.order_of_key(x);
        ord_set.insert(x);
    }

    cout << inv << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}