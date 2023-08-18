/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.
 * NOTE: it is recommended to use this even if you don't
 * understand the following code.
 */

#include <bits/stdc++.h>

using namespace std;

// input data
int N, M;
vector<vector<int>> P;
vector<double> R;

int main() {
//  uncomment the following lines if you want to read/write from files
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

    cin >> N >> M;
    P.resize(N);
    R.resize(N);
    for (int i=0; i<N; i++) {
        P[i].resize(M);
        R[i] = 0.0;
    }
    for (int j=0; j<M; j++)
        for (int i=0; i<N; i++)
            cin >> P[i][j];

    for (int j = 0; j < M; j++) {
        int total = 0;
        for (int i = 0; i < N; i++) total += P[i][j];
        double scaling = 1e6 / total;
        for (int i = 0; i < N; i++) R[i] += scaling * P[i][j];
    }
    
    double tot = M;
    
    for (int i=0; i<N; i++)
        cout << (int)(R[i] / tot) << " "; // print the result
    cout << endl;
    return 0;
}