#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'000

struct Fenwick {
    vector<int> arr;

    void add(int x, int d) {
        for (; x < arr.size(); x += x & -x)
            arr[x] += d;
    }

    int sum(int x) {
        int ans = 0;
        for (; x; x -= x & -x)
            ans += arr[x];
        return ans;
    }

    int binsearch(int val) {
        int curr = 0;
        int sum = 0;
        for (int h = 16; h >= 0; h--) {
            if (curr + (1 << h) >= arr.size()) continue;
            if (sum + arr[curr + (1 << h)] < val) {
                curr += (1 << h);
                sum += arr[curr];
            }
        }
        return curr;
    }

    Fenwick(int size) : arr(size + 1) { }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    Fenwick fenwick(n);
    set<int> ones;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        fenwick.add(i + 1, a[i]);
        if (a[i] == 1) ones.insert(i + 1);
    }

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int s; cin >> s;

            int r = fenwick.binsearch(s);
            //cerr << "\t" << r << endl;

            if (r == n) {
                cout << "NO\n";
                continue;
            }

            int as = fenwick.sum(r + 1);

            //cerr << r << " " << as << " " << *ones.begin() << " " << *ones.rbegin() << endl; 

            if (as == s) {
                cout << "YES\n";
                continue;
            }

            if (!ones.empty() && *ones.rbegin() > r + 1) {
                cout << "YES\n";
                continue;
            }

            if (!ones.empty() && *ones.begin() <= n - r) {
                cout << "YES\n";
                continue;
            }

            cout << "NO\n";
        } else {
            int p, v; cin >> p >> v;
            ones.erase(p);
            fenwick.add(p, -a[p - 1]);
            a[p - 1] = v;
            fenwick.add(p, a[p - 1]);
            if (v == 1) ones.insert(p);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}