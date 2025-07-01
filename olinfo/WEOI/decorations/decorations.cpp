#include <bits/stdc++.h>
using namespace std;


vector<vector<short>> psv_lo;
vector<vector<short>> psv_hi;
vector<vector<short>> psd_lo;
vector<vector<short>> psd_hi;

bool binary_solve(int N, vector<short> row) {
    psv_lo[1] = psv_hi[1] = psd_lo[1] = psd_hi[1] = row;

    for (int len = 2; len <= N; len++) {
        int rng = len - (len + 1) / 2;
        int total = rng * (rng + 3) / 2;

        int sum = psv_lo[len - 1][0] - psv_lo[len - 1 - rng][0];
        for (int i = 1; i <= rng; i++)
            sum += psd_lo[len - i][1] - (N > 2 + rng - 1 ? psd_lo[len - 1 - rng][2 + rng - i] : 0);

        psv_hi[len][0] = psv_hi[len - 1][0] + (sum != 0);
        psd_hi[len][0] = (N > 1 ? psd_hi[len - 1][1] : 0) + (sum != 0);

        for (int l = 1; l <= N - len; l++) {
            sum += psd_lo[len - 1][l + 1] - (N > l + 1 + rng ? psd_lo[len - 1 - rng][l + 1 + rng] : 0);
            sum -= psv_lo[len - 1][l - 1] - psv_lo[len - 1 - rng][l - 1];

            psv_hi[len][l] = psv_hi[len - 1][l] + (sum != 0);
            psd_hi[len][l] = (N > l + 1 ? psd_hi[len - 1][l + 1] : 0) + (sum != 0);
        }

        sum = psv_hi[len - 1][0] - psv_hi[len - 1 - rng][0];
        for (int i = 1; i <= rng; i++)
            sum += psd_hi[len - i][1] - (N > 2 + rng - 1 ? psd_hi[len - 1 - rng][2 + rng - i] : 0);

        psv_lo[len][0] = psv_lo[len - 1][0] + (sum == total);
        psd_lo[len][0] = (N > 1 ? psd_lo[len - 1][1] : 0) + (sum == total);

        for (int l = 1; l <= N - len; l++) {
            sum += psd_hi[len - 1][l + 1] - (N > l + 1 + rng ? psd_hi[len - 1 - rng][l + 1 + rng] : 0);
            sum -= psv_hi[len - 1][l - 1] - psv_hi[len - 1 - rng][l - 1];

            psv_lo[len][l] = psv_lo[len - 1][l] + (sum == total);
            psd_lo[len][l] = (N > l + 1 ? psd_lo[len - 1][l + 1] : 0) + (sum == total);
        }
    }

    return psv_hi[N][0] - psv_hi[N - 1][0];
}

int decorate(int N, vector<int> A) {
    psv_lo.resize(N + 1, vector<short>(N));
    psv_hi.resize(N + 1, vector<short>(N));
    psd_lo.resize(N + 1, vector<short>(N));
    psd_hi.resize(N + 1, vector<short>(N));
    vector<int> vals = A;
    sort(vals.begin(), vals.end());
    return *prev(partition_point(vals.begin(), vals.end(), [&](int val) {
        vector<short> test(N);
        transform(A.begin(), A.end(), test.begin(), [&](int x) { return x >= val; });
        return binary_solve(N, test);
    }));
}
