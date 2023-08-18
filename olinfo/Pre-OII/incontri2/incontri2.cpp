#include <stdbool.h>

bool visita(int N, int A[]) {
    long long sum_emil = 0;
    for (int i = 0; i < N; i++)
        sum_emil += A[i];
    
    long long sum_gemma = 0;
    for (int i = N - 1; i >= 0; i--) {
        if (sum_gemma == sum_emil - A[i]) return true;
        sum_gemma += A[i];
        sum_emil -= A[i];
    }
    if (sum_gemma == sum_emil) return true;
    return false;
}