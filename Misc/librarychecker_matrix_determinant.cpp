#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 998244353;

int fexp(int base, int exp) {
    int ans = 1;
    do {
        if (exp & 1) ans = (long long)ans * base % MOD;
        base = (long long)base * base % MOD;
    } while (exp >>= 1);
    return ans;
}

class Matrix {
    vector<vector<int>> mat;

    int sort_rows() {
        int k = 1;
        
        vector<int> first(mat.size());
        for (int i = 0; i < mat.size(); i++)
            first[i] = find_if_not(mat[i].begin(), mat[i].end(), [](int x) { return x == 0; }) - mat[i].begin();

        for (int i = mat.size(); i >= 0; i--) {
            for (int j = 0; j < i - 1; j++) {
                if (first[j] > first[j + 1]) {
                    swap(mat[j], mat[j + 1]);
                    swap(first[j], first[j + 1]);
                    k = k * (MOD - 1LL) % MOD;
                }
            }
        }

        return k;
    }

    optional<int> gauss() {
        int k = 1;

        for (int i = 0; i < mat.size(); i++) {
            k = (long long)k * sort_rows() % MOD;

            if (mat[i][i] == 0)
                return {};

            int inv = fexp(mat[i][i], MOD - 2);
            k = (long long)k * inv % MOD;

            for (int j = 0; j < mat.size(); j++) {
                mat[i][j] = (long long)mat[i][j] * inv % MOD;
            }

            for (int j = 0; j < mat.size(); j++) {
                if (i == j)
                    continue;
                
                int fac = (MOD - mat[j][i]) % MOD;
                for (int l = 0; l < mat.size(); l++) {
                    mat[j][l] = (mat[j][l] + (long long)fac * mat[i][l]) % MOD;
                }
            }
        }

        return k;
    }

public:

    int det() {
        optional<int> k = gauss();
        
        if (!k)
            return 0;
    
        return fexp(k.value(), MOD - 2);
    }

    Matrix(const vector<vector<int>> &mat) : mat(mat) { }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int N; cin >> N;
    
    vector<vector<int>> mat(N, vector<int>(N));
    for (auto &row: mat)
        for (auto &elem: row)
            cin >> elem;

    Matrix matrix(mat);
    cout << matrix.det() << '\n';
}