#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

template<int K>
struct Matrix {
    long long val[K * K];

    long long* operator[](int idx) {
        return val + K * idx;
    }

    Matrix<K> (initializer_list<long long> arr) {
        memcpy(val, arr.begin(), K * K * sizeof(long long));
    }

    Matrix<K> (int N) {
        memset(val, 0, K * K * sizeof(long long));
        if (N)
            for (int i = 0; i < K; i++)
                val[i * K + i] = 1;
    }
};

template<int K>
Matrix<K> operator*(Matrix<K> a, Matrix<K> b) {
    Matrix<K> res(0);
    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++)
            for (int k = 0; k < K; k++)
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD;
    return res;
}

template<int K>
Matrix<K> operator^(Matrix<K> a, int power) {
    Matrix<K> res(1), cur = a;
    for (int curr = power; curr; curr >>= 1) {
        if (curr & 1)
            res = res * cur;
        cur = cur * cur;
    }
    return res;
}

const Matrix<2> fib_2_base({
    1, 1,
    1, 0,
});
const Matrix<3> fib_3_base({
    1, 1, 1,
    1, 0, 0,
    0, 1, 0,
});
const Matrix<4> fib_4_base({
    1, 1, 1, 1,
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
});
const Matrix<5> fib_5_base({
    1, 1, 1, 1, 1,
    1, 0, 0, 0, 0,
    0, 1, 0, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 0, 1, 0,
});

int progetti(int N, int K) {
    if (K == 2) return (fib_2_base ^ N)[0][0];
    if (K == 3) return (fib_3_base ^ N)[0][0];
    if (K == 4) return (fib_4_base ^ N)[0][0];
    if (K == 5) return (fib_5_base ^ N)[0][0];
}