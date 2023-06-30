// NOTE: it is recommended to use this even if you don't understand the following code.

#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

// input data
string W;

int main() {
//  uncomment the following lines if you want to read/write from files
//  ifstream cin("input.txt");
//  ofstream cout("output.txt");

    cin >> W;
    reverse(W.begin(), W.end());

    long long tot = 0;
    long long curr = 1;
    for (auto c: W) {
        tot += ((c - 'a') * curr) % MOD;
        tot %= MOD;
        curr *= 26;
        curr %= MOD;
        tot += curr;
        tot %= MOD;
    }
    tot += (MOD - curr);
    tot %= MOD;

    cout << tot << endl; // print the result
    return 0;
}