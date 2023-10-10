#include <bits/stdc++.h>
using namespace std;

int single_xor[][2] = {
    {2000000014, 0},
    {1000000008, 1},
    {1000000008, 1},
    {1000000007, 0},
    {1000000007, 0},
    {1000000007, 0},
    {1000000007, 0},
    {1000000007, 0},
    {1000000007, 0},
    {1000000512, 505},
    {1000000007, 0},
    {1000001536, 1529},
    {1000000007, 0},
    {1000000007, 0},
    {1000013824, 13817},
    {1000013824, 13817},
    {1000000007, 0},
    {1000079360, 79353},
    {1000000007, 0},
    {1000341504, 341497},
    {1000341504, 341497},
    {1000000007, 0},
    {1000000007, 0},
    {1006632960, 6632953},
    {1006632960, 6632953},
    {1006632960, 6632953},
    {1000000007, 0},
    {1073741824, 73741817},
    {1073741824, 73741817},
    {1073741824, 73741817},
};

pair<vector<int>, vector<int>> get(int N, int K, int seed = 0) {
    srand(seed);

    int len = N - 2 - (N & 1);
    vector<int> A(N), B(N);
    unordered_set<int> used;

    for (int i = 0; i < len; i += 2) {
        again:
        int a = rand() % 31;
        int b = rand() % 31;
        int c = rand() % 31;
        int d = rand() % 31;

        if (a == b || a == c || a == d || b == c || b == d || c == d) goto again;
        
        int x1 = (1 << a) | (1 << b);
        int x2 = (1 << c) | (1 << d);
        int y1 = (1 << a) | (1 << c);
        int y2 = (1 << b) | (1 << d);

        if (used.count(x1) || used.count(x2) || used.count(y1) || used.count(y2)) goto again;

        A[i] = x1;
        A[i + 1] = x2;
        B[i] = y1;
        B[i + 1] = y2;

        used.insert(x1);
        used.insert(x2);
        used.insert(y1);
        used.insert(y2);
    }

    int X = accumulate(A.begin(), A.end(), 0, bit_xor()) ^ K;

    if (X == 0 || X > 1e9) return get(N, K, seed + 1);

    if (N & 1) {
        int on, off1 = -1, off2;
        for (int bit = 0; bit < 31; bit++) {
            if (X & (1 << bit)) {
                on = bit;
            } else if (off1 == -1) {
                off1 = bit;
            } else {
                off2 = bit;
            }
        }

        int x1 = X ^ (1 << on) ^ (1 << off1);
        int x2 = (1 << on) ^ (1 << off1) ^ (1 << off2);
        int x3 = (1 << off2);
        int y1 = X ^ (1 << off2);
        int y2 = (1 << off1);
        int y3 = (1 << off1) ^ (1 << off2);

        for (auto x: {x1, x2, x3, y1, y2, y3})
            if (used.count(x))
                return get(N, K, seed + 1);

        A[N - 3] = x1;
        A[N - 2] = x2;
        A[N - 1] = x3;
        B[N - 3] = y1;
        B[N - 2] = y2;
        B[N - 1] = y3;
    } else {
        if (__builtin_popcount(X) >= 2) {
            int x1 = 0, x2 = X;
            int y1 = X & -X, y2 = X - (X & -X);

            if (used.count(x1) || used.count(x2) || used.count(y1) || used.count(y2)) return get(N, K, seed + 1);
        
            A[N - 2] = x1;
            A[N - 1] = x2;
            B[N - 2] = y1;
            B[N - 1] = y2;
        } else {
            int x1 = single_xor[__builtin_ctz(X)][0], y1 = single_xor[__builtin_ctz(X)][1];
            int x2 = x1 ^ X, y2 = y2 ^ X;

            if (used.count(x1) || used.count(x2) || used.count(y1) || used.count(y2)) return get(N, K, seed + 1);
        
            A[N - 2] = x1;
            A[N - 1] = x2;
            B[N - 2] = y1;
            B[N - 1] = y2;
        }
    }

    return {A, B};
}

int main() {
    int N, K; cin >> N >> K;
    
    auto [A, B] = get(N, K);
    for (auto a: A) cout << a << ' '; cout << '\n';
    for (auto b: B) cout << b << ' '; cout << '\n';
}