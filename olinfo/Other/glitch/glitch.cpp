#include <bits/stdc++.h>
using namespace std;

#define MAXL 50'000

struct Hash {
    function<int(int, char)> extend_hash;
    function<int(int, char, int)> shorten_hash;

    Hash (int b, int m) {
        extend_hash = [=](int hash, char c) {
            return ((long long)hash * b + c - 'a') % m;
        };

        vector<int> pows(MAXL + 1);
        pows[0] = 1;
        for (int i = 1; i <= MAXL; i++) pows[i] = (long long)pows[i - 1] * b % m;

        shorten_hash = [=](int hash, char c, int len) {
            return (hash - (c - 'a') * (long long)pows[len - 1] % m + m) % m;
        };
    }
};

Hash h[] = {
    {29, 1'000'000'007},
    {31, 1'000'000'007},
    {37, 1'000'000'007},
    {41, 1'000'000'007},
};

bool find_matches(string S, int l) {
    if (l == 0) return true;
    set<array<int, 4>> hs;
    array<int, 4> hashes = {0, 0, 0, 0};
    for (int i = 0; i < l - 1; i++) {
        for (int j = 0; j < 4; j++) {
            hashes[j] = h[j].extend_hash(hashes[j], S[i]);
        }
    }

    for (int i = l - 1; i < S.size(); i++) {
        for (int j = 0; j < 4; j++) {
            hashes[j] = h[j].extend_hash(hashes[j], S[i]);
        }
        
        if (hs.count(hashes)) return true;
        hs.insert(hashes);

        for (int j = 0; j < 4; j++) {
            hashes[j] = h[j].shorten_hash(hashes[j], S[i - l + 1], l);
        }
    }
    return false;
}

int main() {
    int N; cin >> N;
    string S; cin >> S;

    int l = 0, r = N + 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        
        if (find_matches(S, m)) l = m;
        else r = m;
    }
    cout << l << '\n';
}