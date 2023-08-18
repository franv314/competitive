#include <bits/stdc++.h>
using namespace std;

void Accendi(int N, int acceso[], int pulsante[]) {
    for (int i = N; i > 0; i--) {
        for (int j = 2 * i; j <= N; j += i) acceso[i] ^= pulsante[j];
        if (!acceso[i]) pulsante[i] = 1;
    }
}