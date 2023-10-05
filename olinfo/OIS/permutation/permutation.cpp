#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    vector<int> arr;

    void add(int x) {
        for (; x < arr.size(); x += x & -x)
            arr[x]++;
    }

    int query(int x) {
        int ans = 0;
        for (; x; x -= x & -x)
            ans += arr[x];
        return ans;
    }

    int query(int l, int r) {
        return query(r - 1) - query(l - 1);
    }

    Fenwick(int N) : arr(N + 1) { }
};

void solve() {
    int N; cin >> N;
    vector<int> A(N), inv_A(N + 1);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        inv_A[A[i]] = i + 1;
    }

    vector<long long> pref_inv(N + 1), suff_inv(N + 1);
    vector<long long> suff_mov(N + 1);

    {
        Fenwick fenwick(N);
        for (int i = 1; i <= N; i++) {
            pref_inv[i] = pref_inv[i - 1] + fenwick.query(inv_A[i], N + 1);
            fenwick.add(inv_A[i]);
        }
    }
    {
        Fenwick fenwick(N);
        for (int i = N; i > 0; i--) {
            suff_mov[i - 1] = suff_mov[i] + inv_A[i] - 1 - (N - i);
            suff_inv[i - 1] = suff_inv[i] + fenwick.query(1, inv_A[i]);
            fenwick.add(inv_A[i]);
        }
    }

    long long mi = LLONG_MAX;
    for (int i = 0; i <= N; i++) {
        mi = min(mi, pref_inv[i] + suff_inv[i] + suff_mov[i]);
    }
    cout << mi << '\n';
}

int main() {
    int T; cin >> T;
    while (T--) solve();
}