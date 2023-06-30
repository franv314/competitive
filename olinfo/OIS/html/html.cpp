#include <bits/stdc++.h>
using namespace std;

int unescape(int N, char S[]) {
    
    int pos = 0;
    int rem = 0;
    for (int i = 0; i < N; i++) {
        S[pos] = S[i];
        if (S[i] == '&') {
            while (!strncmp(&S[i + 1], "amp;", 4)) {
                rem += 4;
                i += 4;
            }
        }
        pos++;
    }

    return N - rem;
}


#define MAXN 1000010

char S[MAXN];

int main() {
    FILE *fr, *fw;
    int N, i;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d\n", &N));
    for(i=0; i<N; i++)
        S[i] = getc(fr);

    N = unescape(N, S);
    fprintf(fw, "%d\n", N);
    for(i=0; i<N; i++)
        fprintf(fw, "%c", S[i]);
    fclose(fr);
    fclose(fw);
    return 0;
}