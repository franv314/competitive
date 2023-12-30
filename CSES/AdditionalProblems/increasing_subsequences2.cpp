#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct Fenwick {
    vector<int> arr;

    void add(int x, int v) {
        for (; x < arr.size(); x += x & -x) arr[x] = (arr[x] + v) % MOD;
    }

    int query(int x) {
        int ans = 0;
        for (; x; x -= x & -x) ans = (ans + arr[x]) % MOD;
        return ans;
    }

    Fenwick(int n) : arr(n + 1) { }
};

int main() {    
    int N; cin >> N;
    vector<int> vals(N);
    map<int, int> compress;

    for (auto &c: vals) {
        cin >> c;
        compress[c];
    }
    int i = 2;
    for (auto &[_, c]: compress) c = i++;
    for (auto &c: vals) c = compress[c];

    Fenwick lens(N + 5);
    for (auto c: vals) {
        lens.add(c, 1 + lens.query(c - 1));
    }
    cout << lens.query(N + 5);
}