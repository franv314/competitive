#include <bits/stdc++.h>
#include "deliveries.h"
using namespace std;

struct Info {
	int64_t sum_t;
	int64_t sum_hi, sum_lo;

	void apply_lazy(pair<int64_t, int64_t> lazy) {
		sum_hi += lazy.first * sum_t;
		sum_lo += lazy.second * sum_t;
	}
};

Info merge(Info x, Info y) {
	return {x.sum_t + y.sum_t, x.sum_hi + y.sum_hi, x.sum_lo + y.sum_lo};
}

class SegTree {
	int s;
	vector<Info> arr;
	vector<pair<int64_t, int64_t>> lazy;

	void update(int nb, int ne, int n) {
		arr[n].apply_lazy(lazy[n]);
		if (nb + 1 != ne) {
			lazy[2 * n].first += lazy[n].first;
			lazy[2 * n].second += lazy[n].second;
			lazy[2 * n + 1].first += lazy[n].first;
			lazy[2 * n + 1].second += lazy[n].second;
		}
		lazy[n] = {0, 0};
	}

	void update(int l, int r, pair<int64_t, int64_t> upd, int nb, int ne, int n) {
		update(nb, ne, n);
		if (nb >= r || ne <= l) return;
		if (l <= nb && ne <= r) {
			lazy[n].first += upd.first;
			lazy[n].second += upd.second;
			update(nb, ne, n);
			return;
		}
		update(l, r, upd, nb, (nb + ne) / 2, 2 * n);
		update(l, r, upd, (nb + ne) / 2, ne, 2 * n + 1);

		arr[n] = merge(arr[2 * n], arr[2 * n + 1]);
	}

	pair<int64_t, int64_t> query(int l, int r, int nb, int ne, int n) {
		update(nb, ne, n);
		if (nb >= r || ne <= l) return {0, 0};
		if (l <= nb && ne <= r) return {arr[n].sum_hi, arr[n].sum_lo};

		auto [l_hi, l_lo] = query(l, r, nb, (nb + ne) / 2, 2 * n);
		auto [r_hi, r_lo] = query(l, r, (nb + ne) / 2, ne, 2 * n + 1);
		return {l_hi + r_hi, l_lo + r_lo};
	}

public:

	void update(int l, int r, pair<int64_t, int64_t> upd) {
		update(l, r, upd, 0, s, 1);
	}

	pair<int64_t, int64_t> query(int l, int r) {
		return query(l, r, 0, s, 1);
	}

	SegTree() {}
	SegTree(int size, vector<Info> data) :
		arr(4 * size), lazy(4 * size)
	{
		s = 1 << (int)(ceil(log2(size)));

		for (int i = 0; i < size; i++)
			arr[i + s] = data[i];
		for (int i = s - 1; i > 0; i--)
			arr[i] = merge(arr[2 * i], arr[2 * i + 1]);
	}
};

struct Fenwick {
	vector<int64_t> arr;

	void update(int x, int d) {
		for (; x < arr.size(); x += x & -x)
			arr[x] += d;
	}

	int64_t query(int x) {
		int64_t ans = 0;
		for (; x; x -= x & -x)
			ans += arr[x];
		return ans;
	}

	int64_t query(int l, int r) {
		return query(r - 1) - query(l - 1);
	}

	Fenwick() {}
	Fenwick(int n) : arr(n + 1) { }
};

struct Node {
	int dfs_in, dfs_out;
	int hld_start, hld_end, hld_pos;

	int deliveries;

	vector<int> children;
	int parent;
	int edge_weight;
	bool is_heavy;
};

int N;
SegTree hld;
Fenwick deliveries;
vector<int> hld_order;
vector<Node> nodes;

void init(int N, vector<int> U, vector<int> V, vector<int> T, vector<int> W) {
	::N = N;
	nodes.resize(N);
	deliveries = Fenwick(N);
	W[0]++;

	vector<vector<pair<int, int>>> adj(N);
	for (int i = 0; i < N - 1; i++) {
		adj[U[i]].emplace_back(V[i], T[i]);
		adj[V[i]].emplace_back(U[i], T[i]);
	}

	int dfs_pos = 1;
	vector<int> leafs;

	function<int(int, int)> dfs = [&](int node, int par) {
		deliveries.update(dfs_pos, W[node]);
		nodes[node].deliveries = W[node];
		nodes[node].dfs_in = dfs_pos++;

		int size = 1;
		pair<int, int> biggest_child = {INT_MIN, -1};
		for (auto [c, w]: adj[node]) {
			if (c == par) continue;

			nodes[node].children.push_back(c);
			nodes[c].parent = node;
			nodes[c].edge_weight = w;

			int c_size = dfs(c, node);
			size += c_size;
			biggest_child = max(biggest_child, make_pair(c_size, c));
		}

		if (biggest_child.second != -1) {
			nodes[biggest_child.second].is_heavy = true;
		} else {
			leafs.push_back(node);
		}

		nodes[node].dfs_out = dfs_pos;
		return size;
	};

	dfs(0, -1);
	nodes[0].parent = -1;

	vector<Info> hld_arr;
	hld_arr.reserve(N);

	int64_t total = deliveries.query(N);

	for (auto leaf: leafs) {
		int start = hld_arr.size();
		for (int l = leaf; l >= 0; l = (nodes[l].is_heavy ? nodes[l].parent : -1)) {
			int64_t del = deliveries.query(nodes[l].dfs_in, nodes[l].dfs_out);
			hld_arr.push_back({
				nodes[l].edge_weight,
				nodes[l].edge_weight * (total - del),
				nodes[l].edge_weight * del
			});
			hld_order.push_back(l);
		}
		int end = hld_arr.size();

		for (int i = start; i < end; i++) {
			nodes[hld_order[i]].hld_start = start;
			nodes[hld_order[i]].hld_end = end;
			nodes[hld_order[i]].hld_pos = i;
		}
	}

	hld = SegTree(N, hld_arr);
}

long long max_time(int S, int X) {
	if (S == 0) X++;
	int diff = X - nodes[S].deliveries;
	nodes[S].deliveries = X;

	deliveries.update(nodes[S].dfs_in, diff);

	hld.update(0, N, {diff, 0});
	for (
		int curr = S;
		curr != -1;
		curr = nodes[hld_order[nodes[curr].hld_end - 1]].parent
	) {
		hld.update(nodes[curr].hld_pos, nodes[curr].hld_end, {-diff, diff});
	}

	int64_t total = deliveries.query(1, N + 1);

	int node = 0;
	for (;;) {
		int on_path = *partition_point(
			hld_order.begin() + nodes[node].hld_start,
			hld_order.begin() + nodes[node].hld_pos + 1,
			[&](int n) {
				return deliveries.query(nodes[n].dfs_in, nodes[n].dfs_out) * 2 < total;
			}
		);

		int l = nodes[on_path].dfs_in + 1;
		auto ch = partition_point(
			nodes[on_path].children.begin(),
			nodes[on_path].children.end(),
			[&](int n) {
				return deliveries.query(l, nodes[n].dfs_out) * 2 < total;
			}
		);

		if (
			ch == nodes[on_path].children.end() ||
			deliveries.query(nodes[*ch].dfs_in, nodes[*ch].dfs_out) * 2 < total
		) {
			node = on_path;
			break;
		}
		node = *ch;
	}

	int64_t ans = hld.query(0, N).second;
	for (
		int curr = node;
		curr != -1;
		curr = nodes[hld_order[nodes[curr].hld_end - 1]].parent
	) {
		auto [hi, lo] = hld.query(nodes[curr].hld_pos, nodes[curr].hld_end);
		ans += hi - lo;
	}

	return 2 * ans;
}
