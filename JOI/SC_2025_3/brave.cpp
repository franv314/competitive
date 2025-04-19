#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

i64 L, total_score, T, N;
vector<pair<i64, i64>> starts;
vector<i64> hp, H, P;

i64 check(i64 d) {
    if (d > L) return 2e18;
    i64 penalty = total_score * d;

    int stidx = 0;
    priority_queue<pair<i64, i64>> alives;

    i64 t = 0;
    for (i64 i = 0; i < N; i++)
        hp[i] = d * H[i];
    while (stidx < starts.size() || !alives.empty()) {
        bool new_start = alives.empty() || (stidx < starts.size() && starts[stidx].first < t + hp[alives.top().second]);

        if (new_start) {
            auto [nt, idx] = starts[stidx++];
            // cerr << "New monster at time " << nt << " index " << idx << "\n";
            if (!alives.empty()) {
                auto [coeff, i] = alives.top();
                // cerr << "Hitting " << i << " for " << nt - t << "\n";
                hp[i] -= nt - t;
                penalty -= (nt - t) * coeff;
            }
            alives.emplace(P[idx], idx);
            t = nt;
        } else {
            auto [coeff, i] = alives.top(); alives.pop();
            if (t + hp[i] > T) {
                // cerr << "Time's up " << i << "\n";
                hp[i] -= T - t;
                penalty -= (T - t) * coeff;
                break;
            }
            // cerr << "Killing " << i << "\n";
            t += hp[i];
            penalty -= hp[i] * coeff;
            hp[i] = 0;
        }
    }

    return penalty;
}

vector<i64> solve(i64 N, i64 L, i64 T, i64 Q, vector<i64> S, vector<i64> H, vector<i64> P, vector<i64> M) {
    i64 total_score = 0;
    for (i64 i = 0; i < N; i++) {
        total_score += (i64)H[i] * P[i];
    }
    vector<i64> hp(N);
    vector<pair<i64, i64>> starts;
    for (int i = 0; i < N; i++)
        starts.emplace_back(S[i], i);
    sort(starts.begin(), starts.end());

    ::N = N, ::L = L, ::T = T, ::starts = starts, ::total_score = total_score, ::hp = hp, ::H = H, ::P = P;

    vector<i64> ans(Q);
    if (Q > 3) {
        vector<i64> times(L + 1);
        for (int i = 0; i <= L; i += 4) {
            times[i] = check(i);
        }

        int sf = 0;

        for (i64 i = 0; i < Q; i++) {
            while (sf + 4 <= L && times[sf + 4] <= M[i])
                sf += 4;
            
            if (check(sf + 2) <= M[i]) {
                if (check(sf + 3) <= M[i]) {
                    ans[i] = sf + 3;
                } else {
                    ans[i] = sf + 2;
                }
            } else {
                if (check(sf + 1) <= M[i]) {
                    ans[i] = sf + 1;
                } else {
                    ans[i] = sf;
                }
            }
        }
    } else {
        for (i64 i = 0; i < Q; i++) {
            i64 l = i ? ans[i - 1] : 0, r = L + 1;
            while (r - l > 1) {
                i64 m = (l + r) / 2;
                
                if (check(m) <= M[i]) l = m;
                else r = m;
            }
    
            ans[i] = l;
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    i64 N, L; cin >> N >> L;
    i64 T; cin >> T;

    vector<i64> S(N), H(N), P(N);
    for (i64 i = 0; i < N; i++)
        cin >> S[i] >> H[i] >> P[i];

    i64 Q; cin >> Q;
    vector<i64> M(Q);
    for (auto &x: M)
        cin >> x;
    
    vector<i64> ans = solve(N, L, T, Q, std::move(S), std::move(H), std::move(P), std::move(M));

    for (auto x: ans)
        cout << x << '\n';
}