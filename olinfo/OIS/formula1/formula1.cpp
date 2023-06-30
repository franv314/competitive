#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

struct Car {
    int id;
    long long pos;
};

bool operator<(Car a, Car b){
    if (a.pos != b.pos) return a.pos > b.pos;
    return a.id < b.id;
}

bool operator>(Car a, Car b){
    if (a.pos != b.pos) return a.pos < b.pos;
    return a.id > b.id;
}

void quick_select(Car arr[], int start, int end, int k) {
    if (start >= end) return;
    Car pivot = arr[(start + end) / 2];
    
    int i = start - 1, j = end + 1;
    for (;;) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);

        if (i >= j) break;
        swap(arr[i], arr[j]);
    }
    if (k <= j) quick_select(arr, start, j, k);
    else quick_select(arr, j + 1, end, k);
}

inline void fastscan(long long &number) {
    register int c;
    for (c = getchar(); c > 47; c = getchar())
        number = number * 10 + c - 48;
}

long long A[2000], B[2000], C[2000];
long long N, Q, P, T;

int main() {
    fastscan(N);

    Car cars[N];
    for (int i = 0; i < N; i++) {
        fastscan(A[i]);
        fastscan(B[i]);
        fastscan(C[i]);
    }

    fastscan(Q);

    while(Q--) {
        fastscan(P);
        fastscan(T);
        for (int j = 0; j < N; j++)
            cars[j] = (Car){j, A[j] * T * T + B[j] * T + C[j]};
        quick_select(cars, 0, N - 1, P - 1);
        cout << cars[P - 1].id + 1 << "\n";
        P = T = 0;
    }

    return 0;
}