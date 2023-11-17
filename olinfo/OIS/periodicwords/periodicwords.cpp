#include <bits/stdc++.h>
using namespace std;

typedef uint64_t hash_t;
constexpr hash_t B = 29;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N; cin >> N;
    string S; cin >> S;

    vector<hash_t> p_hash(N + 1);
    vector<hash_t> pows(N + 1, 1);
    for (int i = 0; i < N; i++) {
        p_hash[i + 1] = p_hash[i] * B + S[i] - 'a';
        pows[i + 1] = B * pows[i];
    }

    vector<vector<int>> divisors(N + 1);
    for (int i = 1; i <= N; i++) {
        for (int j = 2 * i; j <= N; j += i) {
            divisors[j].push_back(i);
        }
    }

    auto range_hash = [&](int l, int r) {
        return p_hash[r] - (p_hash[l] * pows[r - l]);
    };

    int T; cin >> T;
    while (T--) {
        int l, r; cin >> l >> r;
        r++;

        bool ok = false;
        for (auto i: divisors[r - l]) {
            hash_t h1 = range_hash(l, r - i);
            hash_t h2 = range_hash(l + i, r);

            if (h1 == h2) {
                ok = true;
                break;
            }
        }

        if (ok) cout << "YES\n";
        else cout << "NO\n";
    }
}