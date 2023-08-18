#include <stdio.h>
#include <assert.h>

int bicollatz(int A, int B) { 
    int i;
    for (i = 0; A != 1 || B != 1; i++) {
        int p1 = A & 1, p2 = B & 1;
        if (!p1 && !p2) {
            A /= 2;
            B /= 2;
        } else if (p1 && p2) {
            A = A * 3 + 1;
            B = B * 3 + 1;
        } else if (!p1 && p2)
            B += 3;
        else if (p1 && !p2)
            A += 3;
        if (i > 250000) return -1;
    }
    return i;
}


int main() {
    FILE *fr, *fw;
    int A, B;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(2 == fscanf(fr, "%d %d", &A, &B));

    fprintf(fw, "%d\n", bicollatz(A, B));
    fclose(fr);
    fclose(fw);
    return 0;
}