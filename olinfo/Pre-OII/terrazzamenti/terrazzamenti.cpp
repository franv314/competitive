#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

struct AbsDiff {
    long long h;
    long long operator()(long long a, long long b) { return a + abs(b - (h++)); }
    AbsDiff (long long n) { h = n; }
};

long long stima(int N, int* H) {
    int l = 0;
    int r = 2e9;

    while (l < r) {
        int m = (l + r) / 2;
        long long val_1 = accumulate(H, H + N, 0LL, AbsDiff(m));
        long long val_2 = accumulate(H, H + N, 0LL, AbsDiff(m + 1));

        if (val_1 >= val_2) l = m + 1;
        else r = m;
    }
    return accumulate(H, H + N, 0LL, AbsDiff(l));
}