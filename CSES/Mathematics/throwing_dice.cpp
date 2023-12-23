#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

template<int N>
struct Matrix {
    int mat[N][N];

    Matrix(bool id) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                mat[i][j] = id * (i == j);
    }

    int* operator[](const int &idx) { return mat[idx]; }
    Matrix operator*(Matrix &o) {
        Matrix ans(false);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    ans[i][j] = (ans[i][j] + (long long)mat[i][k] * o[k][j]) % MOD;
                }
            }
        }
        return ans;
    }
    Matrix operator^(long long exp) {
        Matrix base = (*this);
        Matrix ans(true);

        for (; exp; exp >>= 1) {
            if (exp & 1) ans = ans * base;
            base = base * base;
        }

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    long long n; cin >> n;

    Matrix<6> mat(false);
    for (int i = 0; i < 6; i++) mat[i][0] = 1;
    for (int i = 0; i < 5; i++) mat[i][i + 1] = 1;

    Matrix<6> ans = mat ^ n;
    cout << ans[0][0] << '\n';
}