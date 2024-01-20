#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    string S; cin >> S;

    int curr = 0;
    int last = N - 1;

    vector<pair<int, int>> ans;

    for (int i = 0; i < N; i++) {
        if (S[i] == '(') {
            curr++;
        } else if (curr == 0) {
            while (S[last] == ')') last--;
            ans.emplace_back(i, last);
            swap(S[i], S[last]);
            curr++;
        } else {
            curr--;
        }
    }

    cout << ans.size() << '\n';
    for (auto [x, y]: ans) cout << x << ' ' << y << '\n';
}