#include <bits/stdc++.h>
using namespace std;

int collatz(int n) {
    int N = n, i;
    for (i = 1; N != 1; i++) {
        if (N & 1) N = 3 * N + 1;
        else N >>= 1;
    }
    return i;
}

int pollatz(int n) {
    int N = n, i;
    for (i = 1; N != 1; i++) {
        if (N & 1) N = 5 * N + 1;
        else N >>= 1;
        if (i > 10000) return 10000000;
    }
    return i;
}

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    
    int A, B;
    cin >> A >> B;
    
    int count = 0;
    for (int i = A; i <= B; i++)
        count += pollatz(i) < collatz(i);
    cout << count << endl;
    return 0;
}