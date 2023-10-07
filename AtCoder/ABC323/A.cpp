#include <bits/stdc++.h>
using namespace std;

void solve() {
    string S; cin >> S;
    for (int i = 1; i < 16; i += 2) {
        if (S[i] != '0') return void(cout << "No\n");
    }
    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}