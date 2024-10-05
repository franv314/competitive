#include <bits/stdc++.h>
using namespace std;

int main() {
    long long x, y;
    cin >> x >> y;

    string ans = "";
    int count = 1;

    if (y < x) {
        if (y & 1) {
            ans += "C A C\n";
            for (y >>= 1; y; y >>= 1) {
                ans += "C C C\n";
                count++;
                if (y & 1) {
                    ans += "C A A\n";
                    count++;
                }
            }
            ans += "A";
        } else {
            ans += "A A A\n";
            for (y >>= 1; y; y >>= 1) {
                if (y & 1) {
                    ans += "C A C\n";
                    count++;
                }
                ans += "A A A\n";
                count++;
            }
            ans += "C";
        }
    } else {
        if (x & 1) {
            ans += "C B C\n";
            for (x >>= 1; x; x >>= 1) {
                ans += "C C C\n";
                count++;
                if (x & 1) {
                    ans += "C B B\n";
                    count++;
                }
            }
            ans += "B";
        } else {
            ans += "B B B\n";
            for (x >>= 1; x; x >>= 1) {
                if (x & 1) {
                    ans += "C B C\n";
                    count++;
                }
                ans += "B B B\n";
                count++;
            }
            ans += "C";
        }
    }

    cout << count << endl << ans << endl;

    return 0;
}