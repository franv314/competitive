#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, K, M, P, Q; cin >> N >> K >> M >> P >> Q;

    deque<pair<int, long long>> even, odd;
    even.emplace_back(0, Q - P);

    for (int i = 1; i <= N; i++) {
        while (!even.empty() && i - even[0].first > K) even.pop_front();
        while (!odd.empty() && i - odd[0].first > K) odd.pop_front();

        long long best_even = even.empty() ? LLONG_MIN : -even.front().second - M * (i & 1);
        long long best_odd = odd.empty() ? LLONG_MIN : -odd.front().second - M * ((~i) & 1);

        long long best = max(best_even, best_odd);

        if (i & 1) {
            while (!odd.empty() && odd.back().second >= best) odd.pop_back();
            odd.emplace_back(i, best);
        } else {
            while (!even.empty() && even.back().second >= best) even.pop_back();
            even.emplace_back(i, best);
        }
    }

    if (N & 1) cout << odd.back().second << '\n';
    else cout << even.back().second << '\n';
}