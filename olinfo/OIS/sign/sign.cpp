#include <bits/stdc++.h>
using namespace std;

long long T, A, B;

int main() {
    cin >> T;
    for(int _ = 0; _ < T; _++) {
        cin >> A >> B;
        if (A > 0) cout << "+\n";
        else if (B >= 0) cout << "0\n";
        else if (A - B & 1) cout << "+\n";
        else cout << "-\n";
    }
    return 0;
}