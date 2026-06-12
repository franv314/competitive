#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    vector<int> A(N);
    for (auto &x: A) cin >> x;

    int M; cin >> M;
    vector<pair<int, int>> carts(M);

    for (auto ptr : {&pair<int, int>::first, &pair<int, int>::second})
        for (auto &cart: carts)
            cin >> cart.*ptr;
    
    sort(carts.begin(), carts.end());
    vector<int> smax(M + 1, -1), psum(N + 1);
    for (int i = M - 1; i >= 0; i--)
        smax[i] = max(smax[i + 1], carts[i].second);
    for (int i = 0; i < N; i++)
        psum[i + 1] = psum[i] + A[i];
    
    int cur = 0, cnt = 0;
    while (cur < N) {
        int l = cur, r = N;
        while (r - l > 1) {
            int m = (l + r) / 2;
            int idx = lower_bound(carts.begin(), carts.end(), make_pair(m + 1 - cur, -1)) - carts.begin();
            if (smax[idx] >= psum[m + 1] - psum[cur]) l = m;
            else r = m;
        }
        
        cnt++;
        cur = r;
    }
    cout << cnt << '\n';
}