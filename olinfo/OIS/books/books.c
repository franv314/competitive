#include <stdio.h>

int main() {
    int N; scanf("%d", &N);
    
    for (int i = 0; i < N / 2; i++)
        printf("1 0 1\\n");
    printf("%d 0 1\\n", (N + 1) / 2);
    for (int i = 0; i < (N + 1) / 2; i++)
        printf("1 1 0\\n");
    printf("%d 0 1\\n", (N + 1) / 2);
}