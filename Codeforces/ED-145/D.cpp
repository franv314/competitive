#include <bits/stdc++.h>
using namespace std;

const long long c1 = 1e12;
const long long c2 = 1e12 + 1;

int main() {
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        
        long long ans = LLONG_MAX;
        
        int zero = count(s.begin(), s.end(), '0');
        int one = s.size() - zero;

        if (zero == 0 || one == 0) {
            cout << "0\n";
            continue;
        }

        int one_left = 0;
        int zero_right = zero;

        for (int i = 0;; i++) {
            ans = min(ans, c2 * (one_left + zero_right));
            if (i != 0 && i != s.size()) {
                if (s[i - 1] == '1' && s[i] == '0') {
                    ans = min(ans, c1 + c2 * (one_left + zero_right - 2));
                }
            }

            if (i == s.size()) break;
            if (s[i] == '0') zero_right--;
            else one_left++;
        }

        cout << ans << "\n";
    }
}