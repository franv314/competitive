#include <stdio.h>
#include <string.h>

int N;
char s[1000000];

int main() {
    scanf("%d", &N);
    const char fmt[100];

    sprintf(fmt, "%%%ds", N);
    scanf(fmt, s);
    
    for (int i = 1; i <= N; i++) {
        if ((N % i) == 0) {
            for (int j = 0; N - i - j >= N / 2; j += i) {
                if (strncmp(&s[j], &s[N - i - j], i)) goto out;
            }
            printf("%d\n", i);
            return 0;
        }
        out:;
    }
}