#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000003;

int solve(int N, int M, int K, vector<int> A, vector<int> B) {
    vector<pair<bool, int>> lines;
    for (int i = 0; i < N; i++) lines.push_back({false, i});
    for (int i = 0; i < M; i++) lines.push_back({true, i});

    sort(lines.rbegin(), lines.rend(), [&](pair<bool, int> a, pair<bool, int> b) {
        int val_a = a.first ? B[a.second] : A[a.second];
        int val_b = b.first ? B[b.second] : A[b.second];
        return val_a < val_b;
    });

    set<int> rows, cols;
    rows.insert(-1); rows.insert(N);
    cols.insert(-1); cols.insert(M);

    long long rows_total = ((long long)N * N) % MOD;
    long long cols_total = ((long long)M * M) % MOD;
    long long total = 0;

    for (auto [dir, pos]: lines) {
        int val = dir ? B[pos] : A[pos];
        if (!dir) {
            int b = *rows.upper_bound(pos);
            int t = *prev(rows.upper_bound(pos));

            int lo = b - pos;
            int hi = pos - t;

            long long add = ((long long)lo * hi * 2 - 1) % MOD * cols_total % MOD * val % MOD;
            total += add;
            total %= MOD;

            /*cout << dir << " " << pos << endl;
            cout << val << " " << cols_total << " " << b << " " << t << " " << lo << " " << hi << endl;
            cout << add << " " << lo * hi * cols_total << endl;*/

            rows.insert(pos);

            rows_total = (rows_total - ((long long)(b - t - 1) * (b - t - 1) % MOD) + MOD) % MOD;
            rows_total = (rows_total + ((long long)(b - pos - 1) * (b - pos - 1) % MOD) + MOD) % MOD;
            rows_total = (rows_total + ((long long)(pos - t - 1) * (pos - t - 1) % MOD) + MOD) % MOD;
        } else {
            int b = *cols.upper_bound(pos);
            int t = *prev(cols.upper_bound(pos));

            int lo = b - pos;
            int hi = pos - t;

            long long add = ((long long)lo * hi * 2 - 1) % MOD * rows_total % MOD * val % MOD;
            total += add;
            total %= MOD;

            /*cout << dir << " " << pos << endl;
            cout << val << " " << cols_total << " " << b << " " << t << " " << lo << " " << hi << endl;
            cout << add << " " << lo * hi * rows_total << endl;*/

            cols.insert(pos);

            cols_total = (cols_total - ((long long)(b - t - 1) * (b - t - 1) % MOD) + MOD) % MOD;
            cols_total = (cols_total + ((long long)(b - pos - 1) * (b - pos - 1) % MOD) + MOD) % MOD;
            cols_total = (cols_total + ((long long)(pos - t - 1) * (pos - t - 1) % MOD) + MOD) % MOD;
        }
    }

    return total;
}
