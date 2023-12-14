#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    
    if (n % 4 == 1 || n % 4 == 2) {
        cout << "NO\n";
    } else if (n % 4 == 0) {
        cout << "YES\n" << n / 2 << "\n";
        for (int i = 1; i <= n / 4; i++) cout << i << " " << n + 1 - i << " ";
        cout << "\n" << n / 2 << "\n";
        for (int i = n / 4 + 1; i <= n / 2; i++) cout << i << " " << n + 1 - i << " ";
    } else {
        cout << "YES\n" << (n + 1) / 2 << "\n" << (n + 1) / 4 << " " << (n + 1) / 2 << " ";
        for (int i = 1; i <= n / 4; i++) cout << i << " " << n + 1 - i << " ";
        cout << "\n" << n / 2 << "\n" << n + 1 - (n + 1) / 4 << " ";
        for (int i = n / 4 + 2; i <= n / 2; i++) cout << i << " " << n + 1 - i << " ";
    }
}