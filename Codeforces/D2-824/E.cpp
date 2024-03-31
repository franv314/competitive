#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define f first
#define s second
template<class T> using V = vector<T>; 
using vi = V<int>;
using vpi = V<pair<int,int>>;
#define sz(x) int((x).size())
#define pb push_back
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define each(a,x) for (auto& a: x)
#define all(x) begin(x), end(x)
template<class T> bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0; } // set $a = \min(a,b)$
template<class T> bool ckmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0; } // set a = max(a,b)

vpi maxMatch(int L, int R, const vpi& edges) {
	V<vi> adj = V<vi>(L);
	vi nxt(L,-1), prv(R,-1), lev, ptr;
	F0R(i,sz(edges)) adj.at(edges[i].f).pb(edges[i].s);
	while (true) {
		lev = ptr = vi(L); int max_lev = 0;
		queue<int> q; F0R(i,L) if (nxt[i]==-1) lev[i]=1, q.push(i);
		while (sz(q)) {
			int x = q.front(); q.pop();
			for (int y: adj[x]) {
				int z = prv[y];
				if (z == -1) max_lev = lev[x];
				else if (!lev[z]) lev[z] = lev[x]+1, q.push(z);
			}
			if (max_lev) break;
		}
		if (!max_lev) break;
		F0R(i,L) if (lev[i] > max_lev) lev[i] = 0;
		auto dfs = [&](auto self, int x) -> bool {
			for (;ptr[x] < sz(adj[x]);++ptr[x]) {
				int y = adj[x][ptr[x]], z = prv[y];
				if (z == -1 || (lev[z] == lev[x]+1 && self(self,z))) 
					return nxt[x]=y, prv[y]=x, ptr[x]=sz(adj[x]), 1;
			}
			return 0;
		};
		F0R(i,L) if (nxt[i] == -1) dfs(dfs,i);
	}
	vpi ans; F0R(i,L) if (nxt[i] != -1) ans.pb({i,nxt[i]});
	return ans;
}

void solve() {
    int n; cin >> n;
    vector<int> d1(n), d2(n);
    for (auto &x: d1) cin >> x;
    for (auto &x: d2) cin >> x;

    auto check_dumb = [&](int k) -> bool {
        vector<int> x = d1;
        vector<int> y;

        for (int i = 0; i < n; i++) {
            y.push_back(+ d2[i] + k);
            y.push_back(+ d2[i] - k);
            y.push_back(- d2[i] + k);
            y.push_back(- d2[i] - k);
        }

        sort(x.begin(), x.end());
        sort(y.begin(), y.end());

        int i = 0, j = 0, cnt = 0;
        while (i < x.size() && j < y.size()) {
            if (x[i] == y[j]) i++, j++, cnt++;
            else if (x[i] < y[j]) i++;
            else j++;
        }

        return n <= 500 || cnt >= 2 * n;
    };

    auto check = [&](int k) -> bool {
        vector<pair<int, int>> edges;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (
                    d2[j] == + d1[i] + k ||
                    d2[j] == + d1[i] - k ||
                    d2[j] == - d1[i] + k ||
                    d2[j] == - d1[i] - k
                ) {
                    edges.emplace_back(i, j);
                }
            }
        }

        if (edges.size() < n) return false;

        vector<pair<int, int>> matching = maxMatch(n, n, edges);

        if (matching.size() != n) return false;

        vector<int> h1(n);
        for (auto [a, b]: matching) {
            if (d2[b] == d1[a] + k || d2[b] == - d1[a] - k) h1[a] = d1[a];
            else h1[a] = -d1[a];
        }
        sort(h1.begin(), h1.end());
        int d = -min(-k, *min_element(h1.begin(), h1.end()));

        cout << "YES\n";
        for (auto x: h1) cout << x + d << ' '; cout << '\n';
        cout << d << ' ' << d - k << '\n';

        return true;
    };

    for (int i = 0; i < n; i++) {
        if (check_dumb(d1[0] + d2[i]) && check(d1[0] + d2[i])) return;
        if (check_dumb(abs(d1[0] - d2[i])) && check(abs(d1[0] - d2[i]))) return;
    }

    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}