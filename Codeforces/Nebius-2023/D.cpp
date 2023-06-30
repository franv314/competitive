#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    
    int mi_ans = 0, ma_ans = 0;

    for (int i = 0; i < n; i++) {
        string w; cin >> w;
        
        int doubles = 0;
        for (int j = 0; j < m - 1; j++) {
            if (doubles < m / 4 && w[j] == '1' && w[j + 1] == '1') {
                doubles++;
                j++;
            }
        }
        int mi = count(w.begin(), w.end(), '1') - doubles;

        doubles = 0;
        for (int j = 0; j < m - 1; j++) {
            if (doubles < m / 4 && (w[j] == '0' || w[j + 1] == '0')) {
                doubles++;
                j++;
            }
        }
        int ma = count(w.begin(), w.end(), '1') - (m / 4 - doubles);

        mi_ans += mi;
        ma_ans += ma;
    }
    cout << mi_ans << " " << ma_ans;
}