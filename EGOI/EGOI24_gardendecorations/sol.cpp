#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    int n;
    vector<vector<int>> mat;

    Matrix operator*(const Matrix &o) const {
        Matrix ans(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    ans.mat[i][j] ^= mat[i][k] & o.mat[k][j];
        return ans;
    }

    Matrix(int n) : n(n), mat(n, vector<int>(n)) { }
    Matrix(const vector<int> &p) : n(p.size()), mat(n, vector<int>(n)) {
        for (int i = 0; i < n; i++)
            mat[i][p[i]] = 1;
    }
};

Matrix get_from_perm(vector<int> p) {
    int n = p.size();
    Matrix mat(n);

    vector<int> inv(n);
    for (int i = 0; i < n; i++)
        inv[p[i]] = i;
    
    for (int i = 0; i < n; i++)
        mat.mat[i][p[i]] = 1;

    for (int i = n - 1; i >= 0; i--) {
        if (p[i] == i) continue;

        int idx = find(p.begin(), p.end(), i) - p.begin();
        mat.mat[idx][p[i]] = 1;
        p[idx] = p[i];
    }
    
    return Matrix(inv) * mat;
}

Matrix inv(const Matrix &mat) {
    int n = mat.n;
    vector<vector<int>> grid(n, vector<int>(2 * n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = mat.mat[i][j];
            grid[i][j + n] = i == j;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j || !grid[j][i]) continue;
            for (int k = 0; k < 2 * n; k++) {
                grid[j][k] ^= grid[i][k];
            }
        }
    }

    Matrix ans(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans.mat[i][j] = grid[i][j + n];
    return ans;
}

Matrix get_upper_triangular(const Matrix &mat) {
    int n = mat.n;
    Matrix ans = mat;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (ans.mat[j][i])
                for (int k = 0; k < n; k++)
                    ans.mat[j][k] ^= ans.mat[i][k];

    return ans;
}

array<Matrix, 3> lul_decomposition(const vector<int> &perm) {
    Matrix A = get_from_perm(perm);
    Matrix P = Matrix(perm);
    Matrix U = get_upper_triangular(P * A);
    
    return {inv(A), U, (P * A) * inv(U)};
}

struct Vec {
    int n;
    vector<int> vec;

    Vec operator*(const Matrix &o) const {
        Vec ans(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                ans.vec[i] ^= o.mat[i][j] & vec[j];
        return ans;
    }
    Vec(int n) : n(n), vec(n) { }
};

int main() {
    int w; cin >> w;
    
    if (w == 0) {
        cout << 3 << endl;
        return 0;
    }

    int n; cin >> n;
    vector<int> perm(n);
    for (int i = 0; i < n; i++) {
        int v; cin >> v;
        perm[i] = v;
    }

    auto [L1, U, L2] = lul_decomposition(perm);
    Vec state(n);

    if (w == 1) {
        for (int i = 0; i < n; i++) {
            cin >> state.vec[i];
            cout << (state * L1).vec[i] << endl;
        }
    } else if (w == 2) {
        for (int i = n - 1; i >= 0; i--) {
            cin >> state.vec[i];
            cout << (state * U).vec[i] << endl;
        }
    } else if (w == 3) {
        for (int i = 0; i < n; i++) {
            cin >> state.vec[i];
            cout << (state * L2).vec[i] << endl;
        }
    }
}