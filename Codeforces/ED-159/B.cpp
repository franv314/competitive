#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n, P, l, t; cin >> n >> P >> l >> t;

    long long two_days = ((n + 6) / 7) / 2;
    long long one_day = ((n + 6) / 7) % 2;

    long long tdv = 2 * t + l;
    long long odv = t + l;
    long long zdv = l;

    if (two_days * tdv >= P) return void(cout << n - (P + tdv - 1) / tdv << '\n');
    P -= two_days * tdv;
    if (one_day * odv >= P) return void(cout << n - two_days - (P + odv - 1) / odv << '\n');
    P -= one_day * odv;
    cout << n - two_days - one_day - (P + zdv - 1) / zdv << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}