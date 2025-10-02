#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;

    vector<vector<optional<long long>>> grid(N, vector<optional<long long>>(M));
    vector<pair<int, int>> nums;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            string P; cin >> P;
            if (P != "?") {
                grid[i][j] = stoll(P);
                nums.emplace_back(i, j);
            }
        }
    }

    if (N > M) {
        vector<vector<optional<long long>>> ngrid(M, vector<optional<long long>>(N));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                ngrid[j][i] = grid[i][j];
        grid = ngrid;
        swap(N, M);
        for (auto &[i, j]: nums) swap(i, j);
    }

    if (nums.empty())
        return cout << "YES\n", 0;
    
    auto try_pos = [&](int sx, int sy) -> bool {
        if (sx <= 0 || sy <= 0)
            return false;
        for (auto [i, j]: nums)
            if ((long long)(i + sx) * (j + sy) != grid[i][j].value())
                return false;
        return true;
    };

    auto [i, j] = nums[0];
    for (int k = 1; k <= 1e6; k++) {
        long long v = grid[i][j].value();
        if (v % k == 0) {
            if (try_pos(k - i, v / k - j) || try_pos(v / k - i, k - j))
                return cout << "YES\n", 0;
        }
    }

    cout << "NO\n";
}