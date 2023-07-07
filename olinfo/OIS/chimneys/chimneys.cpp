#include <bits/stdc++.h>
#include <climits>
#include <iterator>
using namespace std;

int start;

void subtask2(int N, vector<int> A, vector<int> B, vector<int> L) {
    
}

void subtask3(int N, vector<int> A, vector<int> B, vector<int> L) {
    
}

void subtask4(int N, vector<int> A, vector<int> B, vector<int> L) {
    
}

void subtask5(int N, vector<int> A, vector<int> B, vector<int> L) {
    
}

void subtask6(int N, vector<int> A, vector<int> B, vector<int> L) {
    
}

int main() {
    start = clock();
    int N; cin >> N;
    vector<int> A(N), B(N), L(N);
    unordered_set<int> A_vals, B_vals, L_vals;

    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i] >> L[i];
        A_vals.insert(A[i]);
        B_vals.insert(B[i]);
        L_vals.insert(L[i]);
    }

    subtask5(N, A, B, L);
    return 0;
    
    if (A_vals.size() == N && B_vals.size() == N) subtask2(N, A, B, L);
    else if (B_vals.size() == N) subtask3(N, A, B, L);
    else if (N <= 15) subtask4(N, A, B, L);
    else if (L_vals.size() == 1 && *L_vals.begin() == 1) subtask5(N, A, B, L);
    else subtask6(N, A, B, L);
}