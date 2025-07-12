#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define eb emplace_back

const int none = -1;

using vi = vector<int>;
using iter = vi::iterator;

vi inverse(const vi &p) {
	const int n = p.size();
	vi q(n, none);
	for (int i = 0; i < n; i++) {
		if (p[i] != none) {
			q[p[i]] = i;
		}
	}
	return q;
}

void unit_monge_dmul(const int n, iter stack, const iter a, const iter b) {
	if (n == 1) return stack[0] = 0, void();
	if (n == 2) {
		if (a[0] == 0) copy(b, b + 2, stack);
		else copy(a, a + 2, stack);
		return;
	}
	const iter c_row = stack, c_col = stack + n;
	stack += 2 * n;
	const auto map = [=](const int len, const auto f, const auto g) {
		const iter a_r = stack, a_o = a_r + len, b_r = a_o + len, b_o = b_r + len;
		const auto split = [=](const iter v, iter v_r, iter v_o) {
			for (int i = 0; i < n; i++)
				if (f(v[i])) 
					*(v_r++) = g(v[i]), *(v_o++) = i;
		};
		split(a, a_r, a_o), split(b, b_r, b_o);
		const iter c = stack + 4 * len;
		unit_monge_dmul(len, c, a_r, b_r);
		for (int i = 0; i < len; i++) {
			const int row = a_o[i], col = b_o[c[i]];
			c_row[row] = col, c_col[col] = row;
		}
	};
	const int mid = n / 2;
	map(mid, [mid](const int x) { return x < mid; }, [](const int x) { return x; });
	map(n - mid, [mid](const int x) { return x >= mid; }, [mid](const int x) { return x - mid; });
	for (int row = 0, col = n - 1, sum = 0; row < n; row++) {   
		auto down = [&]() { return (a[row] < mid) ^ (c_row[row] <= col); };
		auto left = [&]() { return -((b[col] < mid) ^ (c_col[col] < row)); };
		while (col >= 0 && sum + left() >= 0) sum += left(), col--;
		if (col >= 0 && sum == 0 && sum + down() > 0) sum += down(), c_row[row] = col;
	}
}

// n*n
vi subunit_monge_dmul(vi a, vi b) {
	const int n = a.size();
	vi a_inv = inverse(a), b_inv = inverse(b), a_row, b_col;
	swap(b, b_inv);
	for (int i = n - 1; i >= 0; i--) 
		if (a[i] != none) 
			a_row.pb(i), a[n - a_row.size()] = a[i];
	reverse(a_row.begin(), a_row.end());
	for (int i = 0, cnt = 0; i < n; i++)
		if (a_inv[i] == none)
			a[cnt++] = i;
	for (int i = 0; i < n; i++) 
		if (b[i] != none) 
			b[b_col.size()] = b[i], b_col.pb(i);
	for (int i = 0, cnt = b_col.size(); i < n; i++)
		if (b_inv[i] == none)
			b[cnt++] = i;
	vi stack(9 * n), c(n, none);
	unit_monge_dmul(n, stack.begin(), a.begin(), b.begin());
	for (int i = 0; i < (int)a_row.size(); i++) {
		const int t = stack[n - a_row.size() + i];
		if (t < int(b_col.size())) c[a_row[i]] = b_col[t];
	}
	return c;
}

vi solve(vi a) {
	if (a.size() == 1) return {-1};
	int n = a.size(), mid = n / 2;
	vi l, r;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] < mid) l.pb(a[i]);
		else r.pb(a[i] - mid);
	}    
	vi tl = solve(l), tr = solve(r), dl(n), dr(n), pl(n), pr(n);
	for (int i = 0, j = 0, k = 0, sl = 0, sr = 0; i < a.size(); i++) {
		if (a[i] < mid) dl[j++] = sr, sl++;
		else dr[k++] = sl, sr++; 
	}    
	iota(pl.begin(), pl.end(), 0);
	iota(pr.begin(), pr.end(), 0);
	for (int i = 0, j = 0, k = 0; i < n; i++) {
		if (a[i] < mid) pl[i] = tl[j] + (~tl[j] ? dl[tl[j]] : 0), j++;
		else pr[i] = tr[k] + (~tr[k] ? dr[tr[k]] : 0), k++;
	}
	return subunit_monge_dmul(pl, pr);
};

struct Fenwick {
	vector<int> tr;
	int n;
	
	Fenwick(int n) : n(n) {
		tr.resize(n + 1);
	}
	
	int lowbit(int x) {
		return x & -x;
	}
	
	void add(int x, int v) {
		for (; x <= n; x += lowbit(x))
			tr[x] += v;
	}
	
	int ask(int x) {
		int res = 0;
		for (; x; x -= lowbit(x))
			res += tr[x];
		return res;
	}
};

void solve() {
    int n; cin >> n;
    vector<int> a1(n), a2(n);
    for (int i = 0; i < n; i++) {
        cin >> a1[i];
        a1[i]--;
        a2[i] = n - 1 - a1[i];
    }

    auto p1 = solve(a1);
    auto p2 = solve(a2);

    vector<int> l(n), r(n, n + 1);
    iota(l.begin(), l.end(), 1);

    for (;;) {
        vector<optional<int>> v(n);
        int q = 0;
        for (int i = 0; i < n; i++) {
            if (r[i] - l[i] > 1) {
                v[i] = (l[i] + r[i]) / 2;
                q++;
            }
        }
        
        if (q == 0)
            break;

        Fenwick tr1(n), tr2(n);
        vi ans1(n), ans2(n);

        for (int i = n - 1; ~i; i--) {
            if (p1[i] != -1) tr1.add(p1[i] + 1, 1);

            if (v[i]) {
                int r = v[i].value();
                ans1[i] = r - i - tr1.ask(r);
            }

            if (p2[i] != -1) tr2.add(p2[i] + 1, 1);
            if (v[i]) {
                int r = v[i].value();
                ans2[i] = r - i - tr2.ask(r);
            }
        }

        for (int i = 0; i < n; i++) {
            if (r[i] - l[i] > 1) {
                if (ans1[i] + ans2[i] == (l[i] + r[i]) / 2 - i + 1)
                    l[i] = (l[i] + r[i]) / 2;
                else
                    r[i] = (l[i] + r[i]) / 2;
                q++;
            }
        }
    }

    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += l[i] - i;
    cout << sum << '\n';
}

// int main() {
// 	cin.tie(0)->sync_with_stdio(false);
// 	int n, q;
// 	cin >> n >> q;
// 	vi a(n);
// 	for (auto& x : a) {
// 		cin >> x;
// 	} 
// 	auto p = solve(a);
// 	vector<vector<pair<int, int>>> v(n + 1);
// 	for (int i = 0; i < q; i++) {
// 		int l, r;
// 		cin >> l >> r;
// 		v[l].emplace_back(i, r);
// 	}
// 	Fenwick tr(n);
// 	vi ans(q);
// 	for (int i = n - 1; ~i; i--) {
// 		if (p[i] != -1) tr.add(p[i] + 1, 1);
// 		for (auto [id, r] : v[i]) {
// 			ans[id] = r - i - tr.ask(r);
// 		}
// 	}  
// 	for (auto& x : ans) {
// 		cout << x << '\n';
// 	}
// 	return 0;
// }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
