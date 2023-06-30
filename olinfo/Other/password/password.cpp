#include <bits/stdc++.h>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");
const int MOD = 1e9 + 7;

int N;
long long K, temp;
unordered_map<long long, long long> cnt;

int main() {
    long long total = 0;

    in >> N >> K;
    for (int _ = 0; _ < N; _++) {
        in >> temp;
        cnt[temp] = (cnt[temp] + 1) % MOD;
    }

    long long i;
    for (i = 1; i * i < K; i++) {
        if (K % i == 0) {
            total = (total + cnt[i] * cnt[K / i]) % MOD;
        }
    }

    if (i * i == K) {
        total = (total + cnt[i] * (cnt[i] - 1) / 2) % MOD;
    }

    out << total << endl;

    return 0;
}