// NOTE: it is recommended to use this even if you don't understand the following code.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// constraints
#define MAXN 6

// input data
int N, i;
char L[MAXN];

int main() {
//  uncomment the following lines if you want to read/write from files
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

    assert(1 == scanf("%d\n", &N));
    for(i=0; i<N; i++)
        assert(1 == scanf("%c ", &L[i]));

    int _ = 0;
    for(int i = 0; i < N; i++) _ += (L[i] == '_');
    
    int tot = 1;
    for (int curr = 26 - N + _; curr > 26 - N; curr--) tot*=curr;

    printf("%d\n", tot); // print the result
    return 0;
}
