#include <stdio.h>
#include <unistd.h>
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")

#define CHUNK 0xffff

char buf[CHUNK];

long long somma(FILE* f) {
    long long s = 0;
    int t = 0;
    int status = 0;
    int size;

    int fp = fileno(f);

    while (size = read(fp, buf, CHUNK)) {
        for (int i = 0; i < size; i++) {
            char c = buf[i];
            if (c >= '0') {
                t = (t * 10) + (c - 48);
            } else if (c == '-') {
                status = -1;
            } else {
                s += t * status;
                t = 0;
                status = 1;
            }
        }
    }
    return s + t;
}