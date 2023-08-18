#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    
    int N, i;
    cin >> N;
    for (i = 1; N != 1; i++) {
        if (N & 1) N = 3 * N + 1;
        else N >>= 1;
    }
    cout << i;
    return 0;
}