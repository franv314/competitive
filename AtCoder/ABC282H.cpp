#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
    vector<vector<pair<long long, int>>> mat;

    pair<long long, int> query(int l, int r) {
        int h = log2(r - l);
        return min(mat[h][l], mat[h][r - (1 << h)]);
    }

    SparseTable(const vector<long long> &arr) {
        int h = log2(arr.size());
        mat.emplace_back(arr.size());

        for (int i = 0; i < arr.size(); i++) {
            mat[0][i] = {arr[i], i};
        }
        for (int i = 1; i <= h; i++) {
            mat.emplace_back(arr.size());
            for (int j = 0; j < arr.size(); j++) {
                mat[i][j] = min(mat[i - 1][j], mat[i - 1][min(j + (1 << (i - 1)), (int)arr.size() - 1)]);
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    long long S; cin >> S;

    vector<long long> A(N);
    vector<int> B(N);
    for (auto &x: A) cin >> x;
    for (auto &x: B) cin >> x;

    vector<long long> ps(N + 1);
    for (int i = 0; i < N; i++) ps[i + 1] = ps[i] + B[i];

    SparseTable st(A);

    function<long long(int, int)> rec = [&](int l, int r) -> long long {
        if (l == r) return 0;

        auto [mi, mi_idx] = st.query(l, r);
        long long curr_ans = 0;
        if (mi_idx - l <= r - mi_idx) {
            for (int i = mi_idx; i >= l; i--) {
                int lo = mi_idx, hi = r + 1;
                while (lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    if (mi + ps[mid] - ps[i] <= S) lo = mid;
                    else hi = mid;
                }
                curr_ans += lo - mi_idx;
            }
        } else {
            for (int i = mi_idx + 1; i <= r; i++) {
                int lo = l - 1, hi = mi_idx + 1;
                while (lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    if (mi + ps[i] - ps[mid] <= S) hi = mid;
                    else lo = mid;
                }
                curr_ans += mi_idx + 1 - hi;
            }
        }

        return curr_ans + rec(l, mi_idx) + rec(mi_idx + 1, r);
    };

    cout << rec(0, N) << '\n';
}