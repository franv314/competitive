#include <bits/stdc++.h>
using namespace std;

template<int N>
struct Matrix {
    long long mat[N][N];

    Matrix(bool id) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                mat[i][j] = (id && i == j) ? 0 : 2e18;
    }

    long long* operator[](const int &idx) { return mat[idx]; }
    Matrix operator*(Matrix &o) {
        Matrix ans(false);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    ans[i][j] = min(ans[i][j], mat[i][k] + o[k][j]);
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
    int n, m, k; cin >> n >> m >> k;

    Matrix<100> mat(false);

    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >>  c;
        mat[a - 1][b - 1] = min(mat[a - 1][b - 1], (long long)c);
    }

    Matrix<100> ans = mat ^ k;
    
    if (ans[0][n - 1] == 2e18) cout << "-1\n";
    else cout << ans[0][n - 1] << '\n';
}