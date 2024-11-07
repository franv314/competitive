#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

i64 qry(i64 l, i64 r) {
    cout << "xor " << l << " " << r << endl;
    i64 ans; cin >> ans;
    return ans;
}

void ans(i64 a, i64 b, i64 c) {
    cout << "ans " << a << " " << b << " " << c << endl;
}

void solve() {
    i64 n; cin >> n;

    i64 fst, snd, trd;
    i64 tot = qry(1, n);

    if (tot) {
        i64 l = 0, r = n;
        while (r - l > 1) {
            i64 m = (l + r) / 2;

            if (qry(1, m)) r = m;
            else l = m;
        }

        fst = r;
    } else {
        i64 curr_max = 2;
        while (curr_max * 2 <= n)
            curr_max *= 2;
        while (!qry(1, curr_max))
            curr_max /= 2;

        i64 l = 0, r = curr_max;
        while (r - l > 1) {
            i64 m = (l + r) / 2;

            if (qry(1, m)) r = m;
            else l = m;
        }

        fst = r;
    }

    {
        i64 l = fst, r = n;
        while (r - l > 1) {
            i64 m = (l + r) / 2;

            if (qry(fst + 1, m)) r = m;
            else l = m;
        }

        snd = r;
    }

    trd = fst ^ snd ^ tot;

    ans(fst, snd, trd);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
