#include <bits/stdc++.h>
using namespace std;

int Confronta(int a, int b);

int Trova(int N, int G) {
    auto check = [&](int a, int b) {
        if (a <= 0) return 0;
        if (b <= 0) return 1;
        if (a > N) return 1;
        if (b > N) return 0;
    
        return Confronta(a, b + N);
    };

    int l = 0, r = N + 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        int m2 = G - m;

        if (m2 > N || (m2 >= 0 && !check(m, m2 + 1))) l = m;
        else r = m;
    };

    int x = G - l;
    if (check(l, x)) return l;
    return N + x;
}