#include <bits/stdc++.h>
using namespace std;

#define MAXS 1'000'001

constexpr int MOD = 918382547;
constexpr long long B1 = 29;
constexpr long long B2 = 31;

void solve() {
    int n; cin >> n;
    vector<string> s(n);
    for (auto &x: s) cin >> x;

    mt19937 rng(77);
    vector<int> alphabet(26);
    iota(alphabet.begin(), alphabet.end(), 0);
    shuffle(alphabet.begin(), alphabet.end(), rng);

    vector<unordered_map<long long, pair<long long, long long>>> hashes(MAXS);
    for (auto &x: s) {
        int h1 = 0;
        int h2 = 0;
        for (int i = 0; i < x.size(); i++) {
            h1 = (h1 * B1 + alphabet[x[i] - 'a']) % MOD;
            h2 = (h2 * B2 + alphabet[x[i] - 'a']) % MOD;
            long long h = (long long)h1 << 32 | h2;

            auto &mref = hashes[i + 1][h];
            mref.first++;
            mref.second += x.size();
        }
    }

    long long ans = 0;

    long long total_length = 0;
    for (auto &x: s) total_length += x.size();

    for (auto &x: s) {
        long long rem_strings = n;
        long long rem_len = total_length;
        reverse(x.begin(), x.end());
        int h1 = 0;
        int h2 = 0;

        for (int i = 0; i < x.size(); i++) {
            h1 = (h1 * B1 + alphabet[x[i] - 'a']) % MOD;
            h2 = (h2 * B2 + alphabet[x[i] - 'a']) % MOD;
            
            long long h = (long long)h1 << 32 | h2;

            auto [match_no, match_len] = hashes[i + 1][h];
            long long unmatch_no = rem_strings - match_no;

            ans += (rem_len - match_len) - i * unmatch_no + (x.size() - i) * unmatch_no;

            rem_strings = match_no;
            rem_len = match_len;
        }
        ans += (rem_len) - x.size() * rem_strings;
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}