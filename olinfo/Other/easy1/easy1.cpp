#include <bits/stdc++.h>
using namespace std;

int main() {
    register int m = -2000;
    int curr, N;
    
    scanf("%d", &N);
    while (N--) {
        scanf("%d", &curr);
        m = max(m, curr);
    }
    printf("%d\n", m);
}