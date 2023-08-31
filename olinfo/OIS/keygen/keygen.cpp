#include <bits/stdc++.h>
#include <immintrin.h>
#pragma GCC target("avx2")
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

    __m256i total = _mm256_set1_epi16(0);
    for (uint16_t i = 0; i < (1 << 15); i += 0x10) {
        __m256i input = _mm256_set_epi16(
            i + 0x0, i + 0x1, i + 0x2, i + 0x3,
            i + 0x4, i + 0x5, i + 0x6, i + 0x7,
            i + 0x8, i + 0x9, i + 0xA, i + 0xB,
            i + 0xC, i + 0xD, i + 0xE, i + 0xF
        );

        __m256i accumulator = _mm256_set1_epi16(0);
        for (auto [or_mask_16, xor_mask_16]: expr) {
            __m256i or_mask = _mm256_set1_epi16(or_mask_16);
            __m256i xor_mask = _mm256_set1_epi16(xor_mask_16);
            __m256i result = or_mask | (input ^ xor_mask);
            result = _mm256_cmpeq_epi16(result, _mm256_set1_epi16(0x7FFF));
            accumulator ^= result;
        }
        total += accumulator & _mm256_set1_epi16(1);
    }

    int res = 0;
    res += _mm256_extract_epi16(total, 0x0);
    res += _mm256_extract_epi16(total, 0x1);
    res += _mm256_extract_epi16(total, 0x2);
    res += _mm256_extract_epi16(total, 0x3);
    res += _mm256_extract_epi16(total, 0x4);
    res += _mm256_extract_epi16(total, 0x5);
    res += _mm256_extract_epi16(total, 0x6);
    res += _mm256_extract_epi16(total, 0x7);
    res += _mm256_extract_epi16(total, 0x8);
    res += _mm256_extract_epi16(total, 0x9);
    res += _mm256_extract_epi16(total, 0xA);
    res += _mm256_extract_epi16(total, 0xB);
    res += _mm256_extract_epi16(total, 0xC);
    res += _mm256_extract_epi16(total, 0xD);
    res += _mm256_extract_epi16(total, 0xE);
    res += _mm256_extract_epi16(total, 0xF);
    
    cout << (res >> (15 - K)) << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int T; cin >> T;
    while (T--) solve();
}