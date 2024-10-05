#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> h;
vector<long long> sum;

int main() {
    cin >> n >> k;
    h.resize(n);
    sum.resize(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        sum[i + 1] = sum[i] + h[i];
    }

    long long ma = INT_MIN;
    list<int> decreasing;
    for (int i = n - 1; i >= 0; i--) {
        decreasing.push_front(i);
        int g = h[i];
        for (auto it = next(decreasing.begin()); it != decreasing.end(); it++) {
            int ng = __gcd(g, h[*it]);
            if (g == ng) {
                it--;
                decreasing.erase(next(it));
            } else {
                if (*it - i >= k)
                    ma = max(ma, g * (sum[*it] - sum[i]));
                g = ng;
            }
        }
        if (n - i >= k)
            ma = max(ma, g * (sum[n] - sum[i]));
    }
    cout << ma << endl;
}
