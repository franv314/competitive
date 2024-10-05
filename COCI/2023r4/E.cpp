#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    vector<long long> arr;

    void add(int x, long long v) {
        for (; x < arr.size(); x += x & -x)
            arr[x] += v;
    }

    int binsearch(long long v) {
        int taken = 0;
        long long curr = 0;
        for (int bit = floor(log2(arr.size())); bit >= 0; bit--) {
            int add = 1 << bit;
            if (taken + add < arr.size() && curr + arr[taken + add] <= v) {
                curr += arr[taken + add];
                taken += add;
            }
        }
        return taken;
    }

    Fenwick(int size) : arr(size + 1) { }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<array<int, 3>> q(n);

    for (int i = 0; i < n; i++) {
        cin >> q[i][0] >> q[i][1];
        q[i][2] = i;
    }

    sort(q.begin(), q.end());

    int last = -1;
    vector<long long> eq(1);

    for (auto &[v, a, i]: q) {
        if (v != last) {
            eq.push_back(last = v);
        }
        v = eq.size() - 1;
        swap(i, v);
    }

    sort(q.begin(), q.end());

    Fenwick fenwick(eq.size());
    long long total = 0;
    for (auto [_, a, v]: q) {
        total += a;
        fenwick.add(v, a);
        
        cout << eq[1 + fenwick.binsearch(total & 1 ? total / 2 : total / 2 - 1)] << "\n";
    }
}