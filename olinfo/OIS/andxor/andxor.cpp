#include <bits/stdc++.h>
using namespace std;

#define MAXBIT 20

int bitxor[MAXBIT];
int am[MAXBIT];

int ans() {
    int ma = INT_MIN;
    for (int i = 0; i < MAXBIT; i++) {
        //cout << i << " " << am[i] << " " << bitxor[i] << endl;
        ma = max(ma, am[i] - !bitxor[i]);
    }
    return ma;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    
    int N, Q; cin >> N >> Q;
    
    vector<int> V(N);
    for (auto &v: V) {
        cin >> v;
        for (int i = 0; i < MAXBIT; i++) {
            if (v & (1 << i)) {
                bitxor[i] ^= v;
                am[i]++;
            }
        }
    }

    cout << ans() << "\n";
    
    while (Q--) {
        int pos, val; cin >> pos >> val;
        pos--;
        for (int i = 0; i < MAXBIT; i++) {
            if (V[pos] & (1 << i)) {
                bitxor[i] ^= V[pos];
                am[i]--;
            }
        }
        for (int i = 0; i < MAXBIT; i++) {
            if (val & (1 << i)) {
                bitxor[i] ^= val;
                am[i]++;
            }
        }
        V[pos] = val;
        cout << ans() << "\n";
    }
}