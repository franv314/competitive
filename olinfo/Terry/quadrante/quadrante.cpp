#include <bits/stdc++.h>
using namespace std;

void solve(int t) {
    int N;
    cin >> N;

    vector<int> X(N), Y(N);
    for(int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
    }

    int i;
    map<int, pair<int, int>> mima;
    mima[INT_MAX] = {INT_MAX, INT_MAX};
    mima[INT_MIN] = {INT_MIN, INT_MIN};

    for (i = 0; i < N; i++) {
        auto it = mima.upper_bound(Y[i]);
        if (it->second.first < X[i]) break;

        it = prev(it);
        if (it->first == Y[i]) it = prev(it);
        else mima[Y[i]] = {INT_MAX, INT_MIN};

        if (it->second.second > X[i]) break;

        mima[Y[i]].second = max(mima[Y[i]].second, X[i]);
        mima[Y[i]].first = min(mima[Y[i]].first, X[i]);
    }

    cout << "Case #" << t << ": " << i << "\n";
}

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}
