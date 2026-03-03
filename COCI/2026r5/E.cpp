#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;
using i64 = long long;

struct Mat2 {
    array<array<i64, 2>, 2> mat;

    Mat2(array<array<i64, 2>, 2> arr) : mat(arr) { }
};

Mat2 operator*(Mat2 a, Mat2 b) {
    Mat2 ans(array<array<i64, 2>, 2>{array<i64, 2>{0, 0}, array<i64, 2>{0, 0}});
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                ans.mat[i][j] = (ans.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % MOD;
    return ans;
}

Mat2 fexpm(Mat2 a, i64 e) {
    Mat2 ans(array<array<i64, 2>, 2>{array<i64, 2>{1, 0}, array<i64, 2>{0, 1}});
    do {
        if (e & 1) ans = ans * a;
        a = a * a;
    } while (e >>= 1);
    return ans;
}

i64 fexp(i64 b, i64 e) {
    i64 ans = 1;
    do {
        if (e & 1) ans = ans * b % MOD;
        b = b * b % MOD;
    } while (e >>= 1);
    return ans;
}

Mat2 fib(array<array<i64, 2>, 2>{array<i64, 2>{1, 1}, array<i64, 2>{1, 0}});

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k; cin >> n >> k;

    if (k < n) {
        cout << "0\n";
        return 0;
    }

    i64 cnt = fexpm(fib, n).mat[0][0];
    i64 poss = fexp(k, n);
    cout << (cnt * fexp(poss, MOD - 2)) % MOD << '\n';
}