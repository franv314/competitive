#include <bits/stdc++.h>
using namespace std;

long long revenue(int N, int K, vector<long long> A) {
    long long ma = 0;
    map<long long, int> cnt;
    for (auto a: A) {
        if (a < 0) cnt[-a]--;
        if (a > 0) cnt[a]++;
    }

    long long sum = 0;
    for (auto [h, c]: cnt) sum += h * c;

    if (cnt.empty()) return 0;
    ma = max(ma, sum - K * cnt.rbegin()->first);

    while (cnt.size() > 1) {
        auto [old_value, old_cnt] = *prev(cnt.end()); cnt.erase(prev(cnt.end()));
        auto &[new_value, new_cnt] = *prev(cnt.end());

        sum -= (old_value - new_value) * old_cnt;
        new_cnt += old_cnt;

        long long rev = sum - K * new_value;
        ma = max(ma, rev);
    }
    return ma;
}
