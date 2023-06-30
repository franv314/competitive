#include <bits/stdc++.h>
using namespace std;

#define is_prime(x) (!is_not_prime[x])

int N, B, P;
vector<int> L;
array<int, 10> D;
vector<bool> is_not_prime(1e6, false);

void sieve() {
    for (int i = 2; i < 1e6; i++)
        if (is_prime(i))
            for (int j = 2 * i; j < 1e6; j += i)
                is_not_prime[j] = true;
    is_not_prime[1] = true;
}

int price(int label) {
    int price = B;
    if (is_prime(label)) 
        price += label + P;

    int sum = 0, prod = 1;    
    for (int d = label; d; d /= 10) {
        sum += d % 10;
        prod *= d % 10;
        price += D[d % 10];
    }
    if (is_prime(sum)) price += sum;
    if (is_prime(prod)) price += prod;
    return price;
}

int best(int label) {
    int ma = 0;
    for (int digit = 1; digit <= label; digit *= 10) {
        int base = digit * 10 * (label / (digit * 10)) + label % digit;

        if (digit * 10 < label)
            ma = max(ma, price(base));
        for (int add = 1; add < 10; add++)
            ma = max(ma, price(base + add * digit));
    }
    return ma;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    L.resize(N);
    for (int _ = 0; _ < N; _++)
        cin >> L[_];
    cin >> B >> P;
    cin >> D[2] >> D[3] >> D[5] >> D[7];

    sieve();

    long long total_sum = 0;
    for (auto label: L)
        total_sum += best(label);
    cout << total_sum << endl;
    
    return 0;
}