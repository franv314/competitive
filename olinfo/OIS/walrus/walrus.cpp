#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N; cin >> N;
    string S; cin >> S;
    S.push_back('-');

    int cc = 0, last = 0;
    vector<int> time;

    for (int i = 0; i <= N; i++) {
        if (S[i] == '-') {
            if (i - last > 0) {
                cc++;
                time.push_back((i - last) / 2 + 1);
            }
            last = i + 1;
        }
    }
    sort(time.rbegin(), time.rend());
    int time_ans = 0;
    for (int i = 0; i < cc; i++)
        time_ans = max(time_ans, time[i] + i);

    cout << cc << ' ' << time_ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) solve();
}