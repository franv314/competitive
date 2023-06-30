// NOTE: it is recommended to use this even if you don't understand the following code.

#include <bits/stdc++.h>
using namespace std;

// input data
int N, K, T, Q;
vector<int> C, U;

int main() {
    cin >> N >> K;
    C.resize(N);
    U.resize(N);
    for (int i=0; i<N; i++)
        cin >> C[i];

    long long cost = 0;
    for (int i=0; i<K; i++) {
        cin >> T >> Q;
        if (U[T] + Q > C[T]) {
            cost += C[T] - U[T];
            U[T] = Q;
        } else {
            U[T] += Q;
        }
    }

    for (int i = 0; i < N; i++) {
        if (U[i]) cost += C[i] - U[i];
    }

    cout << cost << endl; // print the result
    return 0;
}