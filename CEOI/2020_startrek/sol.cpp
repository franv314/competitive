#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

struct Mat {
    int mat[2][2] = {};

    int* operator[](const int &idx) { return mat[idx]; }

    Mat operator*(Mat &o) {
        Mat ans;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                    (ans[i][k] += ((long long)mat[i][j] * o[j][k]) % MOD) %= MOD;
        return ans;
    }

    Mat operator^(const long long &exp) {
        Mat ans = { .mat = {{1, 0}, {0, 1}} };
        Mat base = *this;

        for (long long e = exp; e; e >>= 1) {
            if (e & 1) ans = base * ans;
            base = base * base;
        }

        return ans;
    }
};

struct Info {
    int total_children, won_children, forceable_w, forceable_l;

    pair<bool, int> get_data() const {
        int lost_children = total_children - won_children;
        if (lost_children == 0) {
            return {false, forceable_w};
        } else if (lost_children == 1) {
            return {true, forceable_l};
        } else {
            return {true, 0};
        }
    }

    void merge_child(const Info &ch) {
        auto [w, f] = ch.get_data();
        total_children++;
        won_children += w;
        
        if (w) forceable_w += f;
        else forceable_l += f;
    }

    void demerge_child(const Info &ch) {
        auto [w, f] = ch.get_data();
        total_children--;
        won_children -= w;

        if (w) forceable_w -= f;
        else forceable_l -= f;
    }

    Info() : total_children(0), won_children(0), forceable_l(0), forceable_w(1) { }
};

int solve(int N, long long D, const vector<vector<int>> &adj) {
    vector<Info> dp(N);
    int w = 0, l = 0;
    Mat trans;

    auto dfs1 = [&](auto &&dfs1, int node, int par = -1) -> void {
        dp[node] = Info();

        for (auto child: adj[node]) {
            if (child == par) continue;
            
            dfs1(dfs1, child, node);
            dp[node].merge_child(dp[child]);
        }
    };

    auto dfs2 = [&](auto &&dfs2, int node, int par = -1) -> void {
        if (par != -1) {
            dp[par].demerge_child(dp[node]);
            dp[node].merge_child(dp[par]);
        }

        auto [ww, ff] = dp[node].get_data();

        if (ww) {
            w++;

            (trans[0][0] += ff) %= MOD;
            (trans[1][0] += N - ff) %= MOD;
            (trans[1][1] += N) %= MOD;
        } else {
            l++;

            (trans[0][0] += N - ff) %= MOD;
            (trans[1][0] += ff) %= MOD;
            (trans[0][1] += N) %= MOD;
        }

        for (auto ch: adj[node])
            if (ch != par)
                dfs2(dfs2, ch, node);

        if (par != -1) {
            dp[node].demerge_child(dp[par]);
            dp[par].merge_child(dp[node]);
        }
    };

    dfs1(dfs1, 0);
    dfs2(dfs2, 0);

    Mat final = trans ^ (D - 1);
    int w_tot = ((long long)w * final[1][1] + (long long)l * final[1][0]) % MOD;
    int l_tot = ((long long)w * final[0][1] + (long long)l * final[0][0]) % MOD; 

    auto [ww, ff] = dp[0].get_data();
    long long ans = 0;
    if (ww) {
        (ans += (long long)(N - ff) * l_tot) %= MOD;
        (ans += (long long)N * w_tot) %= MOD;
    } else {
        (ans += (long long)ff * l_tot) %= MOD;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    
    int N; cin >> N;
    long long D; cin >> D;
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    cout << solve(N, D, adj) << '\n';
}