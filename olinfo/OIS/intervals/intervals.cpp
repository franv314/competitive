#include <bits/stdc++.h>
using namespace std;

// input data
int N;
vector<int> A, B;

int main() {
    cin >> N;
    A.resize(N);
    B.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i];
    }

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    int pos_b = 0;
    for (auto x: A) {
        while (B[pos_b] < x) pos_b++;
        if (B[pos_b] == x) {
            N--;
            pos_b++;
        }
    }

    cout << N << endl;  // print the result
    return 0;
}