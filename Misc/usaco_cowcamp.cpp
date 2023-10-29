#include <bits/stdc++.h>
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
    int T, K; cin >> T >> K;
    vector<f80> p = find_probabilities(T);
    
    f80 dp = 0;
    int curr_time = 0;
    for (int i0 = 0; i0 <= T; i0++) {
        f80 A = 0, B = 0;
        for (int i = 0; i < i0; i++) A += p[i];
        for (int i = i0; i <= T; i++) B += p[i] * i;
        
        function<f80(f80, int)> find_nth = [&](f80 base, int n) {
            return powl(A, n) * base + (powl(A, n) - 1) / (A - 1) * B;
        };
        
        int l = -1, r = K - curr_time + 1;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (find_nth(dp, m) > i0) r = m;
            else l = m;
        }
        
        if (curr_time + r >= K) {
            cout << fixed << setprecision(15) << find_nth(dp, K - curr_time);
            return 0;
        }
        
        dp = find_nth(dp, r);
        curr_time += r;
    }
}