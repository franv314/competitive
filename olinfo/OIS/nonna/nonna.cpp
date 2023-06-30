#include <stdio.h>
#include <assert.h>
#include <cstdio>

using namespace std;

#define MAXN 5000
#define MAXK 5000
#define MAXP 1000000
#define INF 1000000000

int memo[MAXN + 1][MAXK + 1];

int mangia(int N, int K, int P[]) {
    for (int i = 0; i <= K; i++) memo[0][i] = INF;

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            memo[i][j] = memo[i - 1][j];

            if (P[i - 1] < j) {
                if (memo[i][j] > memo[i - 1][j - P[i - 1]] + P[i - 1])
                    memo[i][j] = memo[i - 1][j - P[i - 1]] + P[i - 1];
            } else {
                if (memo[i][j] > P[i - 1])
                    memo[i][j] = P[i - 1];
            }
        }
    }
    return memo[N][K];
}

int P[MAXN];

int main() {
    FILE *fr, *fw;
    int N, K, i;
    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(2 == fscanf(fr, "%d %d", &N, &K));
    for(i=0; i<N; i++)
        assert(1 == fscanf(fr, "%d", &P[i]));

    fprintf(fw, "%d\n", mangia(N, K, P));
    fclose(fr);
    fclose(fw);
    return 0;
}