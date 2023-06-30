#include <bits/stdc++.h>
using namespace std;

#define MAXN 4e6

void evadi(int Q, vector<int>& N) {
    vector<int> phi(MAXN + 1);
    iota(phi.begin(), phi.end(), 0);
    
    for (int i = 2; i <= MAXN; i++)
        if (phi[i] == i)
            for (int j = i; j <= MAXN; j += i)
                phi[j] -= phi[j] / i;
    phi[1] = 0;

    for (int j = 0; j < Q; j++) {
        int n = N[j], sol = 0;
        N[j] = 0;
        for (int i = 1; i * i <= n; i++)
            if ((n % i) == 0)
                N[j] += i * i == n ? phi[i - 1] : phi[i - 1] + phi[n / i - 1];
        
    }
}