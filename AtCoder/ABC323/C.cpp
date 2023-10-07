#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N, M; cin >> N >> M;
    vector<int> A(M);
    vector<string> solves(N);
    for (auto &a: A) cin >> a;

    int max_score = INT_MIN;
    for (int i = 0; i < N; i++) {
        cin >> solves[i];
        int score = i;
        for (int j = 0; j < M; j++) {
            score += (solves[i][j] == 'o') * A[j];
        }
        max_score = max(max_score, score);
    }

    for (int i = 0; i < N; i++) {
        int score = i;
        priority_queue<int> problems;
        for (int j = 0; j < M; j++) {
            if (solves[i][j] == 'o') {
                score += A[j];
            } else {
                problems.push(A[j]);
            }
        }
        int cnt = 0;
        while (score < max_score) {
            score += problems.top(); problems.pop();
            cnt++;
        }
        cout << cnt << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}