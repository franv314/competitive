#include <bits/stdc++.h>
using namespace std;

// input data
int N, M, V;
vector<int> H;

class Seg1D {
    int* ma;
    int size;

    optional<int> up_bound(int l, int r, int m, int n, int nb, int ne) {
        if (l >= ne || r <= nb || ma[n] <= m) return {};
        if (nb + 1 == ne) return nb;
        return up_bound(l, r, m, 2 * n, nb, (nb + ne) / 2) ?:
               up_bound(l, r, m, 2 * n + 1, (nb + ne) / 2, ne);
    }

public:

    optional<int> up_bound(int l, int r, int m) {
        return up_bound(l, r, m, 1, 0, size / 2);
    }

    Seg1D(int N, int vals[]) {
        size = 2 << (int)ceil(log2(N));
        ma = (int*) malloc(size * sizeof(int));

        for (int i = 0; i < N; i++)
            ma[i + size / 2] = vals[i];
        for (int i = size / 2 - 1; i; i--)
            ma[i] = max(ma[2 * i], ma[2 * i + 1]);
    }
};

void solve(int N, int V, vector<int> H, vector<int>& can_reach) {
    int extra_height = V * V / 20;
    Seg1D max_tree(N, H.data());
    
    for (int i = 0; i < N; i++)
        can_reach[i] = max_tree.up_bound(i, N, H[i] + extra_height).value_or(N) - 1;
}

int main() {
    cin >> N >> M >> V;
    H.resize(N);
    for (int i=0; i<N; i++)
        cin >> H[i];

    vector<int> can_reach(N);
    solve(N, V, H, can_reach);
    
    for (int i=0; i<N; i++)
        cout << can_reach[i] << " "; // print the result
    cout << endl;
    return 0;
}