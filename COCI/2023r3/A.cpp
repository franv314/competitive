#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M; cin >> N >> M;

    if (M > N) {
        cout << "NE\n";
        return 0;
    }

    while (M--) {
        int a; cin >> a;
        if (a < 4) {
            cout << "NE\n";
            return 0;
        }
        N -= a / 4;
    }
    cout << (N <= 0 ? "DA\n" : "NE\n");
}