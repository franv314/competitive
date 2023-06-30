#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int N, V[MAXN];
const int MOD = 1e9 + 7;

struct Amount {
    int tot, curr;
} am[MAXN];

int compare_int(const void *_a, const void *_b) {
    return *(int*)_a - *(int*)_b;
}

int compare_amount(const void *_a, const void *_b) {
    return ((struct Amount*)_a)->tot - ((struct Amount*)_b)->tot;
}

int mod_pow(int base, int exp) {
    long long curr = base, ans = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) ans = (ans * curr) % MOD;
        curr = (curr * curr) % MOD;
    }
    return ans;
}

int main(void) {
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++)
        scanf("%d", V + i);
    
    qsort(V, N, sizeof(int), compare_int);
    
    int x = -1, old = -1;
    for (int i = 0; i < N; i++) {
        if (V[i] != old) {
            am[++x].curr = 1;
            old = V[i];
        }
        am[x].tot++;
    }

    qsort(am, x + 1, sizeof(struct Amount), compare_amount);

    int total = 0;

    int start_from = 0;
    for (int k = 0; k < am[x].tot; k++) {
        int c = mod_pow(k + 1, MOD - 2);
        
        long long acc = 1;
        for (int i = start_from; i <= x; i++) {
            am[i].curr = ((long long)am[i].curr * (am[i].tot - k)) % MOD;
            am[i].curr = ((long long)am[i].curr * c) % MOD;

            acc = (acc * (am[i].curr + 1)) % MOD;

            if (am[i].curr == 0)
                start_from = i + 1;
        }
        total = (total + acc) % MOD;
    }

    printf("%d\n", total - am[x].tot + 1);
}