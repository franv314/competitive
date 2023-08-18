#include <stdio.h>
#include <assert.h>

int compra(int N, int M, int A, int B) {
    if (B / M >= A) return A * N;
    else if ((N % M) * A < B) return B * (N / M) + A * (N % M);
    else return B * (1 + N / M);
}

int main() {
    FILE *fr, *fw;
    int N, M, A, B;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    assert(4 == fscanf(fr, "%d%d%d%d", &N, &M, &A, &B));

    fprintf(fw, "%d\n", compra(N, M, A, B));
    fclose(fr);
    fclose(fw);
    return 0;
}