#include <bits/stdc++.h>
using namespace std;

long long N, M, L; 

vector<long long> checks;

int range(long long l, long long r) {
    l = max(l, 0ll);
    r = min(r, L);

    auto fst = lower_bound(checks.begin(), checks.end(), l);
    auto lst = upper_bound(checks.begin(), checks.end(), r);

    return lst - fst;
}

int main() {
    cin >> N >> M >> L;

    for (int i = 0; i < N; i++) {
        long long D; cin >> D;
        checks.push_back(D);
    }
    sort(checks.begin(), checks.end());

    int mi = min(range(0, M), range(L - M, L));
    for (auto i: checks) {
        long long center = i - M - 1;
        
        if (center < 0) center = 0;
        if (center > L) center = L;

        mi = min(mi, range(center - M, center + M));
    }
    cout << mi << endl;
    return 0;
}