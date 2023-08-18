#include <bits/stdc++.h>
using namespace std;

int N, S;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    int old = 0;
    int p = 0, m = 0;
    for (int i = 0; i < N; i++) {
        cin >> S;
        if ((S - old + 3) % 3 == 1) p++;
        if ((S - old + 3) % 3 == 2) m++;
        old = S;
    }

    cout << min(m, p) + abs(m - p) / 3 * 2 + abs(m - p) % 3 << endl;
    
    return 0;
}