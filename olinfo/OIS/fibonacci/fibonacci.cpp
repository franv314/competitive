#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> fib = {
    {2, 2},
    {3, 3},
    {5, 5},
    {13, 13},
    {21, 7},
    {34, 17},
    {55, 11},
    {89, 89},
    {233, 233},
    {377, 29},
    {610, 61},
    {987, 47},
    {1597, 1597},
    {2584, 19},
    {4181, 37},
    {6765, 41},
    {10946, 421},
    {17711, 199},
    {28657, 28657},
    {46368, 23},
    {75025, 3001},
    {121393, 521},
    {196418, 53},
    {317811, 281},
    {514229, 514229},
    {832040, 31},
    {1346269, 557},
    {2178309, 2207},
    {3524578, 19801},
    {5702887, 3571},
    {9227465, 141961},
    {14930352, 107},
    {24157817, 73},
    {39088169, 9349},
    {63245986, 135721},
    {102334155, 2161},
    {165580141, 2789},
    {267914296, 211},
    {433494437, 433494437},
    {701408733, 43},
};

vector<int> pow_8 = {1, 8, 64, 512, 4096, 32768, 262144, 2097152, 16777216, 134217728};
vector<int> pow_144 = {1, 144, 20736, 2985984, 429981696};

void solve() {
    int N; cin >> N;
    long long ans = 0;

    for (int x = 0; x < pow_8.size() && N % pow_8[x] == 0; x++) {
        for (int y = 0; y < pow_144.size() && (N / pow_8[x]) % pow_144[y] == 0; y++) {
            int rem = N / pow_8[x] / pow_144[y];

            long long part = 1;
            int cnt = 0;
            for (int i = 1; i <= x; i++) part = part * (++cnt) / i;
            for (int i = 1; i <= y; i++) part = part * (++cnt) / i;

            for (int i = fib.size() - 1; i >= 0; i--) {
                int j = 0;
                while (rem % fib[i].second == 0) {
                    if (rem % fib[i].first == 0) {
                        part = part * (++cnt) / (++j);
                        rem /= fib[i].first;
                    } else goto fail;
                }
            }

            if (rem == 1) ans += part;

            fail:;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    while (T--) solve();
}