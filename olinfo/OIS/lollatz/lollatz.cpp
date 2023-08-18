#include <stdio.h>
#include <assert.h>

int afaikdiyrotfl(int N) {
    while (N % 10)
        N = (N * (N % 10 - 1)) / 2;
        
    return N;
}


int main() {
    FILE *fr, *fw;
    int N, i;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d", &N));

    fprintf(fw, "%d\n", afaikdiyrotfl(N));
    fclose(fr);
    fclose(fw);
    return 0;
}