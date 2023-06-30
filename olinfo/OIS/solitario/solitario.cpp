#include <stdio.h>
#include <assert.h>

#define MAXR 10
#define MAXC 6
#define GET(bitmask, pos) (bitmask & (1 << (pos)))

int best[11][64][64];

int count(int row) {
    int c = 0;
    for (int i = 0; i < 6; i++) c += !!GET(row, i);
    return c;
}

bool tris(int row_1, int row_2, int row_3, int C) {
    for (int i = 0; i < C; i++)
        if (GET(row_1, i) && GET(row_2, i) && GET(row_3, i)) return true;
    for (int i = 0; i < C - 2; i++)
        if (GET(row_1, i) && GET(row_2, i + 1) && GET(row_3, i + 2)) return true;
    for (int i = 2; i < C; i++)
        if (GET(row_1, i) && GET(row_2, i - 1) && GET(row_3, i - 2)) return true;
    for (int i = 0; i < C - 2; i++) {
        if (GET(row_1, i) && GET(row_1, i + 1) && GET(row_1, i + 2)) return true;
        if (GET(row_2, i) && GET(row_2, i + 1) && GET(row_2, i + 2)) return true;
        if (GET(row_3, i) && GET(row_3, i + 1) && GET(row_3, i + 2)) return true;
    }
    return false;
}

int gioca(int N, int M) {

    if (N * M == 1) return 1;

    int R = N > M ? N : M;
    int C = M > N ? N : M;

    int full_row = 1 << C;

    for (int row = 3; row <= R; row++) {
        for (int row_1 = 0; row_1 < full_row; row_1++) {
            for (int row_2 = 0; row_2 < full_row; row_2++) {
                for (int row_3 = 0; row_3 < full_row; row_3++) {
                    if (tris(row_1, row_2, row_3, C)) continue;
                    if (best[row - 1][row_2][row_3] + count(row_3) > best[row][row_1][row_2]) {
                        best[row][row_1][row_2] = best[row - 1][row_2][row_3] + count(row_3);
                    }
                }
            }
        }
    }
    int result = 0;
    for (int row_1 = 0; row_1 < full_row; row_1++) {
        for (int row_2 = 0; row_2 < full_row; row_2++) {
            if (best[R][row_1][row_2] + count(row_1) + count(row_2) > result) {
                result = best[R][row_1][row_2] + count(row_1) + count(row_2);
            }
        }
    }
    return result;
}


int main() {
    FILE *fr, *fw;
    int N, M;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(2 == fscanf(fr, "%d %d", &N, &M));

    fprintf(fw, "%d\n", gioca(N, M));
    fclose(fr);
    fclose(fw);
    return 0;
}