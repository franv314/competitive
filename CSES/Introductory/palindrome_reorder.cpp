#include <bits/stdc++.h>
using namespace std;

int main() {
    string S; cin >> S;
    string palindrome(S.size(), ' ');
    int taken = 0;
    for (char c = 'A'; c <= 'Z'; c++) {
        int amount = count(S.begin(), S.end(), c);
        
        if (amount & 1) {
            if (palindrome[S.size() / 2] == ' ') {
                palindrome[S.size() / 2] = c;
            } else {
                cout << "NO SOLUTION\n";
                return 0;
            }
        }
        for (; amount >= 2; amount -= 2) {
            palindrome[taken] = palindrome[S.size() - 1 - taken] = c;
            taken++;
        }
    }
    cout << palindrome << "\n";
}