#include <stdbool.h>
#include <stdio.h>

void count_sort(int N, int V[]) {
    int amounts[11] = {};
    for (int i = 0; i < N; i++) amounts[V[i]]++;
    int pos = 0;
    for (int i = 0; i < 11; i++)
        while (amounts[i]--)
            V[pos++] = i;
}

bool associabili(int N, int* v1, int* v2) {
    count_sort(N, v1);
    count_sort(N, v2);
    for (int i = 0; i < N; i++)
        if (v2[i] <= v1[i]) return false;
    return true;
}