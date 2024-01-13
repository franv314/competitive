#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;

    vector<pair<int, int>> a(n), b(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        a[x].first = n - i;
        a[x].second = x;
    }
    
    for (int i = 0; i < n; i++) {
        cin >> b[i].first;
        b[i].second = i;
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<array<int, 3>> rank(n);

    for (int i = 0; i < n; i++) {
        rank[i][2] = i + 1;
        rank[a[i].second][0] += i + 1;
        rank[b[i].second][0] += i + 1;
        rank[b[i].second][1] = i + 1;
    }

    sort(rank.rbegin(), rank.rend());
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". Kod" << (rank[i][2] < 10 ? "0" : "") << rank[i][2] << " (" << rank[i][0] << ")\n";  
    }
}