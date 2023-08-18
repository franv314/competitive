#include <stdio.h>
#include <assert.h>

double _pow(int n) { return n ? 10 * _pow(n-1) : 1; }

long long next(long long x) {
    
    if (x == 3) return 6;
    if (x == 6) return 9;
    if (x == 9) return 36;
    
    int fst = x % 10;
    int snd = (x / 10) % 10;
    
    if ((fst == 3) && (snd == 6)) return x + 6;
    if ((fst == 3) && (snd == 9)) return x + 3;
    if ((fst == 6) && (snd == 3)) return x + 3;
    
    long long y = 10 * next(x / 10);
    if ((y / 10) % 10 == 3) return y + 6;
    else return y + 3;
}

long long occulta(int N, int M) {
    double max = _pow(N);
    long long m = 0;
    for (long long x = 3; x < max; x = next(x)) {
        if (x % M > m) m = x % M;
    }
    return m;
}

int main() {
    FILE *fr, *fw;
    int T, N, M, i;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d", &T));
    for (i=0; i<T; i++) {
        assert(2 == fscanf(fr, "%d %d", &N, &M));
        fprintf(fw, "%d ", occulta(N, M));
    }

    fprintf(fw, "\n");
    fclose(fr);
    fclose(fw);
    return 0;
}