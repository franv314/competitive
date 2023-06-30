#include <bits/stdc++.h>
using namespace std;

namespace USACO {

using ll = long long;
using db = long double;  // or double, if TL is tight
using str = string;      // yay python!

using vl = vector<ll>;
using vi = vector<int>;

#define tcT template <class T
#define tcTU tcT, class U
tcT > using V = vector<T>;
tcT, size_t SZ > using AR = array<T, SZ>;
tcT > using PR = pair<T, T>;

// pairs
#define mp make_pair
#define f first
#define s second

#define sz(x) int((x).size())

// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define each(a, x) for (auto &a : x)

// INPUT
#define tcTUU tcT, class... U
tcT > void re(T &x) { cin >> x; }
tcTUU > void re(T &t, U &...u) {
	re(t);
	re(u...);
}
tcT > void re(V<T> &x) { each(a, x) re(a); }

void setPrec() { cout << fixed << setprecision(15); }
void unsyncIO() { cin.tie(0)->sync_with_stdio(0); }
void setIO() {
	unsyncIO();
	setPrec();
}

#define rep(i, a, b) for (int i = a; i < (b); ++i)
typedef pair<int, int> pii;

typedef complex<double> C;
void fft(vector<C> &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n);
		rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		rep(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
	}
	vi rev(n);
	rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j, 0, k) {
				// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  ///
				// include-line
				auto x = (double *)&rt[j + k],
				     y = (double *)&a[i + j + k];  /// exclude-line
				C z(x[0] * y[0] - x[1] * y[1],
				    x[0] * y[1] + x[1] * y[0]);  /// exclude-line
				a[i + j + k] = a[i + j] - z;
				a[i + j] += z;
			}
}

typedef vector<ll> vl;
vl convMod(int MOD, const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	vl res(sz(a) + sz(b) - 1);
	int B = 32 - __builtin_clz(sz(res)), n = 1 << B, cut = int(sqrt(MOD));
	vector<C> L(n), R(n), outs(n), outl(n);
	rep(i, 0, sz(a)) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
	rep(i, 0, sz(b)) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
	fft(L), fft(R);
	rep(i, 0, n) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	rep(i, 0, sz(res)) {
		ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
		ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
		res[i] = ((av % MOD * cut + bv) % MOD * cut + cv) % MOD;
	}
	return res;
}
}

long long N;
int K, MOD;

int power(int base, long long exp) {
    long long ans = 1, curr = base;
    for (; exp; exp >>= 1) {
        if (exp & 1) ans = ans * curr % MOD;
        curr = curr * curr % MOD;
    }
    return ans;
}
    
vector<long long> convolve(vector<long long> A, vector<long long> B) {
    vector<long long> doubled_B(2 * B.size());
    copy(B.begin(), B.end(), doubled_B.begin());
    copy(B.begin(), B.end(), doubled_B.begin() + B.size());
    
    vector<long long> convolution = USACO::convMod(MOD, A, doubled_B);
    
    vector<long long> ans(B.size());
    copy(convolution.begin() + A.size(), convolution.begin() + 2 * A.size(), ans.begin());
    return ans;
}
    
vector<long long> constarr(long long N, int M, vector<long long> curr) {    
    vector<long long> ans(M);
    ans[0] = 1;
    
    for (; N; N >>= 1) {
        if (N & 1) {
            ans = convolve(ans, curr);
        }
        curr = convolve(curr, curr);
    }
    return ans;
}
    
int main() {
    cin >> N >> K >> MOD;
    
    int ans = 0;
    
    vector<long long> odds, evens;
        
    if (K & 1) {
        {
            vector<long long> base(K, 1);
            base[(K + 1) / 2] = 0;
            odds = constarr(N, K, base);
        }
        {
            vector<long long> base(K, 1);
            base[0] = 0;
            evens = constarr(N, K, base);
        }
    } else {
        {
            vector<long long> base(K, 1);
            odds = constarr(N, K, base);
        }
        {
            vector<long long> base(K, 1);
            base[0] = 0, base[K / 2] = 0;
            evens = constarr(N, K, base);
        }
    }

    for (int target = 0; target < K; target++) {
        if (target & 1) {
            ans = (ans + odds[(K - ((N % K) * (target / 2) % K) + target) % K]) % MOD;
        } else {
            ans = (ans + evens[(K - ((N % K) * (target / 2) % K) + target) % K]) % MOD;
        }
    }

    cout << (power(K, N) - ans + MOD) % MOD << "\n";
}