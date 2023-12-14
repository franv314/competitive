#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    vector<long long> arr;
    
    void add(int x, int diff) {
        for (; x < arr.size(); x += x & -x)
            arr[x] += diff;
    }
    
    long long query(int x) {
        long long ans = 0;
        for (; x; x -= x & -x)
            ans += arr[x];
        return ans;
    }
    
    Fenwick(int size) : arr(size + 1) { }  
};

int main() {
    int N, Q; cin >> N >> Q;
    Fenwick fenwick(N);
    
    int old = 0;
    for (int i = 1; i <= N; i++) {
        int x; cin >> x;
        fenwick.add(i, x - old);
        old = x;
    }
    
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int a, b, u; cin >> a >> b >> u;
            fenwick.add(a, u);
            fenwick.add(b + 1, -u);
        } else {
            int k; cin >> k;
            cout << fenwick.query(k) << '\n';
        }
    }
}