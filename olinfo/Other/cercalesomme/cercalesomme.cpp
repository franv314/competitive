#include <bits/stdc++.h>
using namespace std;

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int N, V[9], S;
    fscanf(input, "%d", &N);
    for (int i = 0; i < N; i++)
        fscanf(input, "%d", &V[i]);
    fscanf(input, "%d", &S);

    for (int i = 0; i < (1 << (N - 1)); i++) {
        int sum = 0, curr = V[0];
        for (int j = 1; j < N; j++) {
            if (i & (1 << (j - 1))) {
                sum += curr;
                curr = 0;
            }
            curr = 10 * curr + V[j];
        }
        if (sum + curr == S) {
            for (int j = 1; j < N; j++) {
                if (i & (1 << (j - 1))) {
                    fprintf(output, "%d ", j);
                }
            }
            putc('\n', output);
        }
    }
}