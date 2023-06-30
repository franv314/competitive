#include <bits/stdc++.h>
using namespace std;

#define TESTS 32

struct Fenwick {
    vector<int> arr, val;

    void add(int x, int v) {
        int diff = v - val[x];
        val[x] = v;
        for (; x < arr.size(); x += x & -x)
            arr[x] += diff;
    }

    int query(int x) {
        int ans = 0;
        for (; x; x -= x & -x)
            ans += arr[x];
        return ans;
    }

    Fenwick() : arr(300'001), val(300'001) { }
} fenwicks[TESTS];

map<int, int> rands;
mt19937 rnd;

int rng(int x) {
    auto it = rands.find(x);
    if (it != rands.end()) return it->second;
    return rands[x] = rnd();
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL), cout.tie(NULL);
    rnd.discard(clock());
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int a; cin >> a;
        int r = rng(a);
        for (int j = 0; j < TESTS; j++) {
            fenwicks[j].add(i, (bool)(r & (1 << j)));
        }
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int i, x; cin >> i >> x;
            int r = rng(x);
            for (int j = 0; j < TESTS; j++) {
                fenwicks[j].add(i, (bool)(r & (1 << j)));
            }
        } else {
            int l, r, k; cin >> l >> r >> k;
            
            bool ok = true;
            for (int j = 0; j < TESTS; j++) {
                if ((fenwicks[j].query(r) - fenwicks[j].query(l - 1)) % k) {
                    ok = false;
                    break;
                }
            }

            cout << (ok ? "YES\n" : "NO\n");
        }
    }
}