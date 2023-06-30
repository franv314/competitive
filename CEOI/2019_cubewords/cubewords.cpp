#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 998'244'353;
constexpr int Σ = 62;

int map_chars(char c) {
    if ('a' <= c && c <= 'z') return c - 'a';
    if ('A' <= c && c <= 'Z') return c - 'A' + 26;
    return c - '0' + 52;
}

bool is_palindrome(string S) {
    for (int i = 0; i < S.size() / 2; i++)
        if (S[i] != S[S.size() - 1 - i])
            return false;
    return true;
}

int perm(int a, int b, int c, int d) {
    if (a == b && b == c && c == d) return 1;
    if ((a == b && b == c) || (b == c && c == d)) return 4;
    if (a == b && c == d) return 6;
    if (a == b || b == c || c == d) return 12;
    return 24;
}

int cnt(array<unordered_map<int, int>, Σ> words) {
    int common_end[Σ][Σ][Σ] = {};
    for (int end = 0; end < Σ; end++)
        for (auto [a, c_a]: words[end])
            for (auto [b, c_b]: words[end])
                for (auto [c, c_c]: words[end])
                    common_end[a][b][c] = (common_end[a][b][c] + (long long)c_a * c_b % MOD * c_c % MOD) % MOD;

    long long ret = 0;

    for (int a = 0; a < Σ; a++)
        for (int b = a; b < Σ; b++)
            for (int c = b; c < Σ; c++)
                for (int d = c; d < Σ; d++)
                    ret = (ret + (long long)common_end[a][b][c] * common_end[a][b][d] % MOD * common_end[a][c][d] % MOD * common_end[b][c][d] % MOD * perm(a, b, c, d) % MOD) % MOD;
    return ret;
}

int main() {
    int N; cin >> N;
    unordered_map<int, array<unordered_map<int, int>, Σ>> words;
    unordered_set<string> found_words;

    while (N--) {
        string S; cin >> S;
        if (found_words.count(S)) continue;

        if (is_palindrome(S)) {
            words[S.size()][map_chars(S.front())][map_chars(S.back())]++;
        } else {
            words[S.size()][map_chars(S.front())][map_chars(S.back())]++;
            words[S.size()][map_chars(S.back())][map_chars(S.front())]++;
        }

        reverse(S.begin(), S.end());
        found_words.insert(S);
    }

    long long ans = 0;
    for (auto [size, words]: words) {
        ans = (ans + cnt(words)) % MOD;
    }
    cout << ans << '\n';
}