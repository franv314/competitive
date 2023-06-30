#include <stdio.h>
#include <assert.h>

#define MAXN 100000

int C;

int days[367];

int main() {
    FILE *fr, *fw;
    int D, N, i;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(2 == fscanf(fr, "%d %d", &D, &N));
    for(i=0; i<N; i++) {
        assert(1 == fscanf(fr, "%d", &C));
        days[C]++;
    }

    for (int i = 1; i <= 7; i++) {
        for (int j = i; j <= D; j += 7) {
            if (days[j] < 10) putc('.', fw);
            else if (days[j] < 20) putc('o', fw);
            else putc('O', fw);
        }
        putc('\n', fw);
    }

    // insert your code here
    
    fclose(fr);
    fclose(fw);
    return 0;
}