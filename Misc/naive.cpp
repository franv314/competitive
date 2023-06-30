#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

typedef long double f80;

vector<f80> find_probabilities(int T) {
    vector<f80> last(T + 1), curr(T + 1);
    last[1] = 1;
    for (int r = 2; r <= T; r++) {
        for (int c = 0; c <= r; c++) {
            curr[c] = 0;
            if (c != 0) curr[c] += last[c - 1] / 2;
            if (c != r) curr[c] += last[c] / 2;
        }
        swap(last, curr);
    }
    return last;
}

int main() {
    cout << fixed << setprecision(15);
    int T, K; cin >> T >> K;
    vector<f80> p = find_probabilities(T);
    vector<f80> vals(T + 1);
    iota(vals.begin(), vals.end(), 0);
    
    for (int i = 1; i <= K; i++) {
        f80 exp = 0;
        for (int i = 0; i <= T; i++) {
            exp += p[i] * vals[i];
        }
        for (int i = 0; i <= exp; i++) vals[i] = exp;
        if (i == K) cout << exp << endl;
    }
}