#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 104857601;

namespace USACO {

using ll = long long;
using db = double;  // or double, if TL is tight
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
vl convMod(const vl &a, const vl &b) {
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

class Poly {
    vector<int> coeffs;

public:
    int degree() { return coeffs.size() - 1; }
    int& operator[](const int &term) { return coeffs[term]; }

    Poly operator+(Poly B) {
        Poly ans(max(degree(), B.degree()));
        for (int i = 0; i <= ans.degree(); i++) {
            if (i <= degree()) ans[i] = (ans[i] + coeffs[i]) % MOD;
            if (i <= B.degree()) ans[i] = (ans[i] + B[i]) % MOD;
        }
        return ans;
    }

    Poly operator*(Poly B) {
        vector<long long> a, b;
        for (auto x: coeffs) a.push_back(x);
        for (auto x: B.coeffs) b.push_back(x);

        vector<long long> m = USACO::convMod(a, b);
        Poly res;
        for (auto x: m) res.coeffs.push_back(x);

        return res;
    }

    Poly operator-() {
        Poly ans(*this);
        for (auto &c: ans.coeffs) c = (MOD - c) % MOD;
        return ans;
    }

    Poly operator-(Poly B) {
        return (*this) + (-B);
    }

    Poly operator~() {
        Poly ans(*this);
        reverse(ans.coeffs.begin(), ans.coeffs.end());
        return ans;
    }

    pair<Poly, Poly> split_at(int l) {
        Poly a, b;
        for (int i = 0; i <= degree(); i++) {
            if (i < l) a.coeffs.push_back(coeffs[i]);
            else b.coeffs.push_back(coeffs[i]);
        }
        return {a, b};
    }

    Poly inverse_mod(int L) {
        Poly a({1});
        for (int l = 1; l <= L; l *= 2) {
            auto [h_0, h_1] = split_at(l);
            h_1.coeffs.resize(l);
            auto [_, c] = (a * h_0).split_at(l);
            c.coeffs.resize(l);

            Poly b = -(a * (h_1 * a + c));
            
            b.coeffs.resize(l);
            for (auto c: b.coeffs) a.coeffs.push_back(c);
        }
        return a;
    }

    pair<Poly, Poly> operator/(Poly B) {
        Poly q = ~(*this) * (~B).inverse_mod(degree() - B.degree());
        q.coeffs.resize(degree() - B.degree() + 1);
        q = ~q;
        Poly r = (*this) - B * q;
        while (r.coeffs.size() > 1 && r.coeffs.back() == 0) r.coeffs.pop_back();
        return {q, r};
    }

    int operator()(int x) {
        int ans = 0;
        for (int i = degree(); i >= 0; i--) {
            ans = ((long long)ans * x + coeffs[i]) % MOD;
        }
        return ans;
    }

    Poly(int degree = -1) : coeffs(degree + 1) { }
    Poly(vector<int> coefficients) : coeffs(coefficients) { }
    Poly(initializer_list<int> coefficients) {
        for (auto x: coefficients)
            coeffs.push_back(x);
    }

    friend ostream& operator<<(ostream &, Poly);
};

ostream& operator<<(ostream &out, Poly poly) {
    for (auto c: poly.coeffs) out << c << " ";
    return out;
}

int *B;
map<pair<int, int>, Poly> mods;

Poly get_mods(int l, int r) {
    if (l + 1 == r) {
        return mods[{l, r}] = Poly({(MOD - B[l]) % MOD, 1});
    }
    Poly poly1 = get_mods(l, (l + r) / 2);
    Poly poly2 = get_mods((l + r) / 2, r);
    return mods[{l, r}] = poly1 * poly2;
}

void get_eval(int l, int r, Poly p) {
    if (l + 1 == r) {
        B[l] = p(l);
        return;
    }
    Poly p_l = (p / mods[{l, (l + r) / 2}]).second;
    Poly p_r = (p / mods[{(l + r) / 2, r}]).second;
    get_eval(l, (l + r) / 2, p_l);
    get_eval((l + r) / 2, r, p_r);
}

int solve(int N, vector<int> R, vector<int> B) {
    ::B = B.data();
	vector<Poly> factors;
    for (auto r: R) factors.push_back({r, 1});

    while (factors.size() > 1) {
        for (int i = 0; i < factors.size() - 1; i += 2) {
            factors[i / 2] = factors[i] * factors[i + 1];
        }
        if (factors.size() % 2 == 1) {
            Poly spare = factors.back();
            factors.resize(factors.size() / 2);
            factors.push_back(spare);
        } else {
            factors.resize(factors.size() / 2);
        }
    }

    get_mods(0, N);
    get_eval(0, N, factors[0]);

    int ans = 1;
    for (auto b: B) {
        ans = ((long long)ans * b) % MOD;
    }
    return ans;
}