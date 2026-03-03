#include <bits/stdc++.h>
using namespace std;

long long eval_sum(int x, int s, int e) {
    int curr = s;
    long long ans = 0;
    e = min(e, x + 1);
    while (curr < e) {
        int div = x / curr;
        int r = (x / div) + 1;

        ans += (long long)(min(e, r) - curr) * (x / curr);
        curr = r;
    }

    return ans;
}

int find_lim(int x, int k) {
    int l = 0, r = k + 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if ((long long)(x / m) * (x + 2) <= (int)1e8) r = m;
        else l = m;
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
 
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    long long sum = 0;
    for (auto x: a) {
        int s = find_lim(x, k);
        sum += (long long)(s - 1) * (long long)1e8;
        sum += (x + 2) * eval_sum(x, s, k + 1);
    }

    cout << sum << '\n';
}