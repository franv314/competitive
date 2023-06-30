#include <bits/stdc++.h>
using namespace std;

int N, K;

int main() {

    cin >> N;
    for (int i=0; i<N; i++) {
        cin >> K;
        bitset<10> digits;
        for (int i = K;; i += K) {
            for (auto c: to_string(i))
                digits[c - '0'] = 1;
            if (digits.all()) {
                cout << i / K << endl;
                break;
            }
        }
    }

    return 0;
}