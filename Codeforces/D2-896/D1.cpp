#include <bits/stdc++.h>
using namespace std;

int is_pow(int x) {
    if (x == 0) return false;
    return x == (x & -x);
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    int64_t tot = accumulate(a.begin(), a.end(), 0LL);
    if (tot % n) return void(cout << "No\n");

    int64_t avg = tot / n;
    multiset<int> given, taken;
    int jolly_given, jolly_taken;

    for (auto x: a) {
        if (x < avg) {
            int diff = avg - x;

            int pow = 1;
            while (pow <= diff) pow *= 2;

            taken.insert(pow);
            given.insert(pow - diff);

            if (!is_pow(pow - diff)) return void(cout << "No\n");
        } else if (x > avg) {
            int diff = x - avg;

            int pow = 1;
            while (pow <= diff) pow *= 2;

            given.insert(pow);
            taken.insert(pow - diff);

            if (!is_pow(pow - diff)) return void(cout << "No\n");
        }
    }

    if (given == taken) cout << "Yes\n";
    else cout << "No\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}