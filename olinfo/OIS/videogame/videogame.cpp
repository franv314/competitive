#include <bits/stdc++.h>
using namespace std;

int main() {
	int T, N; cin >> T >> N;
	
	vector<pair<int, int>> me(N);
	for (auto &[a, b]: me) cin >> a >> b;
	
	int M; cin >> M;
	
	vector<pair<int, int>> he(M);
	for (auto &[a, b]: he) cin >> a >> b;

    sort(me.begin(), me.end());
    sort(he.begin(), he.end());

    long long total = 0;
    int pos_b = 0, last;
    for (auto [start, end]: me) {
        last = start;
        while (he[pos_b].second < start && pos_b < M) {
            pos_b++;
        }
        if (pos_b == M) break;
        while (he[pos_b].first <= end && pos_b < M) {
            if (he[pos_b].first - last > T) break;
            last = he[pos_b].second;
            total += min(end, he[pos_b].second) - max(start, he[pos_b].first) + 1;
            pos_b++;
        }

        pos_b--;
    }

    cout << total << endl; // print the result
    return 0;
}