#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    vector<int> arr;
    int s;

    void update(int p, int v) {
        p += s;
        arr[p] += v;
        for (p >>= 1; p; p >>= 1)
            arr[p] = max(arr[2 * p], arr[2 * p + 1]);
    }

    int lower_bound(int d) {
        if (d > arr[1]) return -1;

        int curr = 1;
        while (curr < s) {
            if (arr[2 * curr] >= d) curr = 2 * curr;
            else curr = 2 * curr + 1;    
        }
        return curr - s;
    }

    int query(int l, int r) {
        int ans = INT_MAX;
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = max(ans, arr[l++]);
            if (r & 1) ans = max(ans, arr[--r]);
        }
        return ans;
    }

    SegTree(const vector<int> &a) {
        s = 1 << (int)ceil(log2(a.size()));
        arr.resize(2 * s);

        copy(a.begin(), a.end(), arr.begin() + s);
        for (int i = s - 1; i; i--) arr[i] = max(arr[2 * i], arr[2 * i + 1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    SegTree segtree(a);

    while (m--) {
        int c; cin >> c;
        int pos = segtree.lower_bound(c);
        
        cout << pos + 1 << ' ';
        if (pos != -1) {
            segtree.update(pos, -c);
        }
    }
}