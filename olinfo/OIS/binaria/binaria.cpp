#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;

    long long ans = 0;
    while (N--) {
        long long x; cin >> x;

        long long last = 1;
        while (last < x)
            last = last * 2 + 1;
        
        ans += last - x;
    }

    cout << ans << '\n';
}
