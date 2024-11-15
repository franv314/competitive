#include <bits/stdc++.h>
using namespace std;

#define int long long

constexpr int MOD = 998244353;

constexpr int R = 996173970;
constexpr int D = 18;
constexpr int L = 1 << D;

int pow_r[D], pow_ir[D];
int temp[L];

int fexp(int b, long long e) {
    if (e < 0) return 0;

    int a = 1;
    for (; e; e >>= 1) {
        if (e & 1) a = (long long)a * b % MOD;
        b = (long long)b * b % MOD;
    }
    return a;
}

void precalc() {
    pow_r[0] = R;
    pow_ir[0] = fexp(R, MOD - 2);

    for (int i = 1; i < D; i++) {
        pow_r[i] = (long long)pow_r[i - 1] * pow_r[i - 1] % MOD;
        pow_ir[i] = (long long)pow_ir[i - 1] * pow_ir[i - 1] % MOD;
    }
}

template<bool inv>
void fft(int arr[], int size, int step, int depth) {
    if (depth == D) return;
 
    int omega = inv ? pow_ir[depth] : pow_r[depth];
    fft<inv>(arr,        size / 2, step * 2, depth + 1);
    fft<inv>(arr + step, size / 2, step * 2, depth + 1);
 
    for (int j = 0; j < size; j++) temp[j] = arr[j * step];
 
    int w = 1;
    for (int j = 0; j < size / 2; j++) {
        arr[j * step] =
            (temp[j * 2] + (long long)w * temp[j * 2 + 1]) % MOD;
        arr[(j + size / 2) * step] =
            (temp[j * 2] - (long long)w * temp[j * 2 + 1] % MOD + MOD) % MOD;
        
        w = (long long)w * omega % MOD;
    }
}

vector<int> prod(vector<int> P, vector<int> Q) {
    int end_size = P.size() + Q.size() - 1;
    int size = 1 << (int)ceil(log2(P.size() + Q.size() - 1));
    int depth = (int)log2(L / size);

    P.resize(size);
    Q.resize(size);
 
    fft<0>(P.data(), size, 1, depth);
    fft<0>(Q.data(), size, 1, depth);

    for (int i = 0; i < size; i++) P[i] = (long long)P[i] * Q[i] % MOD;
    
    fft<1>(P.data(), size, 1, depth);

    int I = fexp(size, MOD - 2);
    for (int i = 0; i < size; i++) P[i] = (long long)P[i] * I % MOD;
 
    P.resize(end_size);
    return P;
}

vector<int> calc(const vector<int> &cc) {
    vector<vector<int>> poly;
    for (auto x: cc) {
        poly.emplace_back(x + 1);
        poly.back()[0] = poly.back().back() = 1;
    }

    while (poly.size() > 1) {
        vector<vector<int>> new_poly;

        for (int i = 0; i + 1 < poly.size(); i += 2) {
            new_poly.push_back(prod(poly[i], poly[i + 1]));
        }

        if (poly.size() % 2)
            new_poly.push_back(poly.back());
        
        poly = new_poly;
    }

    return poly[0];
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    precalc();

    int N, M; cin >> N >> M;
    vector<int> U(M), V(M);
    for (auto &x: U) cin >> x;
    for (auto &x: V) cin >> x;

    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        adj[U[i]].push_back(V[i]);
        adj[V[i]].push_back(U[i]);
    }

    vector<int> cc;
    vector<bool> vis(N);
    for (int i = 0; i < N; i++) {
        if (vis[i]) continue;
        
        int cnt = 0;
        queue<int> q;
        q.push(i);

        while (!q.empty()) {
            int x = q.front(); q.pop();
            if (vis[x]) continue;
            
            cnt++;
            vis[x] = true;

            for (auto y: adj[x])
                q.push(y);
        }

        cc.push_back(cnt);
    }

    vector<int> freq = calc(cc);

    int ans = 0;
    for (int i = 0; i <= N; i++) {
        int part = fexp(2, (long long)i * (i - 1) / 2 + (long long)(N - i) * (N - i - 1) / 2 - M);
        ans = (ans + (long long)part * freq[i]) % MOD;
    }

    cout << ans << '\n';
}