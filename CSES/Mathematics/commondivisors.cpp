#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> cnt(1e6 + 1);
    while (n--) {
        int x; cin >> x;
        cnt[x]++;
    }
    for (int i = 1e6; i > 0; i--) {
        int m = 0;
        for (int j = i; j <= 1e6; j += i) {
            m += cnt[j];
        }
        if (m >= 2) {
            cout << i;
            return 0;
        }
    }
}