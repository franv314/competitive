#include <stdint.h>

uint64_t dec(int N, int d, int p) {
    uint64_t curr = p;
    uint64_t res = 1;
    for (int i = 0; i < 32; i++) {
        if ((d >> i) % 2) {
            res = (res * curr) % N;
        }
        curr = (curr * curr) % N;
    }
    return res;
}

void decifra(int N, int d, int L, int* messaggio, char* plaintext) {
    for (int i = 0; i < L; i++) {
        plaintext[i] = dec(N, d, messaggio[i]);
    }
    plaintext[L] = 0;
}