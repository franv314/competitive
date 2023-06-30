#include <bits/stdc++.h>
using namespace std;

int direziona(int N, vector<int> A, vector<int> B) {
	int pos_a = 0, pos_b = 0;
    int result = 1 - N;
    for (auto x: B) {
        while (A[pos_a++] < x && pos_a <= N) ;
        if (pos_a > N) break;
        result++;
    }
    for (auto x: A) {
        while (B[pos_b++] <= x && pos_b <= N) ;
        if (pos_b > N) break;
        result++;
    }
    return result;
}