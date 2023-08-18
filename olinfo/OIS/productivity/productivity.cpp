/*
 * NOTE: it is recommended to use this even if you don't
 * understand the following code.
 */

#include <bits/stdc++.h>

using namespace std;

// input data
int N, M, E;

int main() {
//  uncomment the following lines if you want to read/write from files
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

    cin >> N >> M >> E;
    int max_ = 0;
    for (int i = M; i <= N; ++i) {
        max_ = max(max_, E % i);
    }

    cout << max_ << endl; // print the result
    return 0;
}