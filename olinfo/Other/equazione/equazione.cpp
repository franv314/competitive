#include <bits/stdc++.h>
using namespace std;

int main() {
    int start = clock();
    long long N; cin >> N;
    int sol = -1;
    for (int x = sqrtl(N); x >= 0; x--) {
        int sum = 0;
        for (int y = x; y; y /= 10) sum += y % 10;
        if ((long long)x * (x + sum) == N) {
            sol = x;
        }
        if (clock() - start >= 0.10 * CLOCKS_PER_SEC) break;
    }
    cout << sol;
}