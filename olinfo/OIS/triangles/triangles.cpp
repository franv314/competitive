#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, Q; cin >> N >> Q;

    vector<int> indeg(N);
    iota(indeg.begin(), indeg.end(), 0);

    long long triangles = 0;

    while (Q--) {
        int u, v; cin >> u >> v;
        u--, v--;

        triangles -= indeg[u]++ - (--indeg[v]);
        cout << triangles << '\n';
    }
}