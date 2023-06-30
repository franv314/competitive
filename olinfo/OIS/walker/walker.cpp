#include <bits/stdc++.h>
using namespace std;

const int MOD = 666'013;

struct Mat2 {
    long long mat[2][2];
};

Mat2 operator*(Mat2 a, Mat2 b) {
    Mat2 result;
    result.mat[0][0] = (a.mat[0][0] * b.mat[0][0] + a.mat[0][1] * b.mat[1][0]) % MOD;
    result.mat[0][1] = (a.mat[0][0] * b.mat[0][1] + a.mat[0][1] * b.mat[1][1]) % MOD;
    result.mat[1][0] = (a.mat[1][0] * b.mat[0][0] + a.mat[1][1] * b.mat[1][0]) % MOD;
    result.mat[1][1] = (a.mat[1][0] * b.mat[0][1] + a.mat[1][1] * b.mat[1][1]) % MOD;
    return result;
}

Mat2 operator^(Mat2 a, long long exp) {
    Mat2 res, curr = a;
    res.mat[0][0] = res.mat[1][1] = 1;
    res.mat[1][0] = res.mat[0][1] = 0;

    for (; exp; exp >>= 1) {
        if (exp & 1) res = res * curr;
        curr = curr * curr;
    }
    return res;
}

int main() {
    long long N, K;
    cin >> N >> K;

    Mat2 my_mat;
    my_mat.mat[0][0] = (N - 2 + MOD) % MOD;
    my_mat.mat[0][1] = (N - 1 + MOD) % MOD;
    my_mat.mat[1][0] = 1;
    my_mat.mat[1][1] = 0;

    my_mat = my_mat ^ (K - 2);

    cout << ((N - 1) * my_mat.mat[0][0]) % MOD << endl;
}