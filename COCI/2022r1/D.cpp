// Task "Iksevi"

#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<
#define MAXN 10'000'000
#define MAXP 664'579

int n, x, y;
vector<int> smallest_prime(MAXN + 1, 0);

void sieve() {
    for (int i = 2; i <= MAXN; i++)
        if (!smallest_prime[i])
            for (int j = i; j <= MAXN; j += i)
                if (!smallest_prime[j])
                    smallest_prime[j] = i;
}

int count_divisors(int n) {
    int ans = 1;
    while (smallest_prime[n]) {
        int curr = smallest_prime[n];
        int count = 0;
        while (n % curr == 0) {
            n /= curr;
            count++;
        }
        ans *= (count + 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();

    cin >> n;
    while (n--) {
        cin >> x >> y;
        
        if (x == 0 && y == 0) {
            cout << "0\n";
            continue;
        }

        while (x % 2 == 0 && y % 2 == 0) x /= 2, y /= 2;
        if (x % 2 == 1 && y % 2 == 1) cout << "0\n";
        else cout << count_divisors(__gcd(x, y)) << "\n";
    }
    return 0;
}