#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N; cin >> N;
    int cnt = 0;
    map<long long, long long> sizes;
    while (N--) {
        int S, C; cin >> S >> C;
        sizes[S] = C;
    } 

    while (!sizes.empty()) {
        auto [size, count] = *sizes.begin(); sizes.erase(sizes.begin());
        if (count > 1) sizes[size * 2] += count / 2;
        cnt += count % 2;
    }
    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}