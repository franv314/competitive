#include <bits/stdc++.h>
#include <immintrin.h>
#pragma GCC optimize("O3")
#pragma GCC target("avx512bw,popcnt")
using namespace std;

void solve() {
    int K; cin >> K;
    string raw_expr; cin >> raw_expr;

    vector<array<uint16_t, 2>> expr;
    int not_flag = 0;
    for (int i = 0; i < raw_expr.size(); i++) {
        char c = raw_expr[i];
        if (c == '(') {
            expr.push_back({0x7FFF, 0});
        } else if (c == '!') {
            not_flag = 1;
        } else if ('a' <= c && c <= 'z') {
            c -= 'a';
            if (!((expr.back()[0] >> c) & 1)) {
                if (((expr.back()[1] >> c) & 1) ^ not_flag) {
                    expr.pop_back();
                    while (i < raw_expr.size() && raw_expr[i] != '^') i++;
                }
            } else {
                expr.back()[0] ^= 1 << c;
                expr.back()[1] |= not_flag << c;
            }
            not_flag = 0;
        }
    }

    int res = 0;
    alignas(32) uint16_t inputs[32];
    iota(inputs, inputs + 32, 0);
    __m512i input = _mm512_load_si512(inputs);
    for (uint16_t i = 0; i < (1 << 15); i += 0x20) {
        __mmask32 accumulator = 0;
        for (auto [or_mask_16, xor_mask_16]: expr) {
            __m512i or_mask = _mm512_set1_epi16(or_mask_16);
            __m512i xor_mask = _mm512_set1_epi16(xor_mask_16);
            __m512i result = or_mask | (input ^ xor_mask);
            accumulator ^= (_mm512_cmpeq_epi16_mask(result, _mm512_set1_epi16(0x7FFF)));
        }
        res += __builtin_popcount(accumulator);

        input += _mm512_set1_epi16(0x20);
    }

    cout << (res >> (15 - K)) << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int T; cin >> T;
    while (T--) solve();
}