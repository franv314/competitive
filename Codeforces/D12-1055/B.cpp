#include <bits/stdc++.h>
using namespace std;

int sus(int n, int rk, int ck, int rd, int cd) {
    return max(
        ((ck != cd) ? max(abs(rk - rd), ck < cd ? cd : n - cd) : -1e9),
        ((rk != rd) ? max(abs(ck - cd), rk < rd ? rd : n - rd) : -1e9)
    );
}

void solve() {
    int n, rk, ck, rd, cd;
    cin >> n >> rk >> ck >> rd >> cd;
    cout << sus(n, rk, ck, rd, cd) << '\n';
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
