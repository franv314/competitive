#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, L; cin >> N >> L;
    vector<pair<int, int>> papers(N);
    for (int i = 0; i < N; i++) {
        cin >> papers[i].first >> papers[i].second;
        if (papers[i].second == -1) papers[i].second = L - 1;
    }

    set<int> days;
    for (int i = 0; i < L; i++) days.insert(i);
    sort(papers.rbegin(), papers.rend());
    
    int total = 0;
    for (auto [P, D]: papers) {
        auto x = days.upper_bound(D);
        if (x != days.begin()) {
            total += P;
            days.erase(prev(x));
        }
    }
    cout << total << endl;
}