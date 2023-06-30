#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'001

long long hsh[MAXN], pxor[MAXN];

struct Fenwick {
    vector<long long> arr, val;

public:

    void set(int x, long long v) {
        long long d = val[x] ^ v;
        val[x] = v;

        for (; x < arr.size(); x += x & -x)
            arr[x] ^= d;
    }

    long long query(int x) {
        long long ans = 0;
        for (; x; x -= x & -x)
            ans ^= arr[x];
        return ans;
    }

    Fenwick() { }
    Fenwick(int size) : arr(size + 1), val(size + 1) { }
} fenwick;

void inizio(int N, int M, int sfere[]) {
    mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
    for (int i = 1; i <= N; i++) {
        hsh[i] = rng();
        pxor[i] = pxor[i - 1] ^ hsh[i];
    }

    fenwick = Fenwick(N);
    for (int i = 0; i < N; i++)
        fenwick.set(i + 1, hsh[sfere[i]]);
}

void modifica(int posizione, int valore) {
    fenwick.set(posizione + 1, hsh[valore]);
}

bool verifica(int l, int r) {
	return (fenwick.query(r + 1) ^ fenwick.query(l)) == pxor[r - l + 1];
}