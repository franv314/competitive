#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

constexpr i64 MOD = 88798426270663591;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string a, b, sum; cin >> a >> b >> sum;

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    reverse(sum.begin(), sum.end());

    vector<i64> pows(a.size() + 1);
    pows[0] = 1;
    for (int i = 1; i <= a.size(); i++)
        pows[i] = pows[i - 1] * 10 % MOD;
    
    i64 sum_mod = 0;
    for (int i = 0; i < sum.size(); i++) {
        sum_mod = (sum_mod + (sum[i] - '0') * pows[i]) % MOD;
    }

    vector<i64> factor(10);
    for (int i = 0; i < a.size(); i++) {
        factor[a[i] - 'A'] = (factor[a[i] - 'A'] + pows[i]) % MOD;
        factor[b[i] - 'A'] = (factor[b[i] - 'A'] + pows[i]) % MOD;
    }

    vector<int> corr(10);
    iota(corr.begin(), corr.end(), 0);

    auto check = [&]() {
        if (corr[a.back() - 'A'] == 0 && a.size() > 1) return false;
        if (corr[b.back() - 'A'] == 0 && b.size() > 1) return false;

        string ans = "";
        bool carry = false;

        for (int i = 0; i < a.size(); i++) {
            int sum = corr[a[i] - 'A'] + corr[b[i] - 'A'] + carry;

            ans += (sum % 10) + '0';
            carry = sum / 10;
        }

        if (carry)
            ans += '1';

        return ans == sum;
    };

    do {
        i64 try_mod = 0;
        for (int i = 0; i < 10; i++) {
            try_mod = (try_mod + corr[i] * factor[i]) % MOD;
        }

        if (try_mod == sum_mod && check()) {
            reverse(a.begin(), a.end());
            reverse(b.begin(), b.end());

            for (auto num: {a, b}) {
                for (auto x: num) {
                    cout << corr[x - 'A'];
                }
                cout << '\n';
            }

            return 0;
        }
    } while (next_permutation(corr.begin(), corr.end()));
}