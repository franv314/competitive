#include <bits/stdc++.h>
#include "vision.h"
using namespace std;

void construct_network(int H, int W, int K) {
	int total = H * W;
	int bits = ceil(log2(max(H, W)));

	auto add_not = [&](int x) {
		::add_not(x);
		return total++;
	};
	auto add_or = [&](vector<int> x) {
		::add_or(x);
		return total++;
	};
	auto add_xor = [&](vector<int> x) {
		::add_xor(x);
		return total++;
	};
	auto add_and = [&](vector<int> x) {
		::add_and(x);
		return total++;
	};

	auto add_adder = [&](int bits, vector<int> a, vector<int> b) {
		assert(a.size() == bits);
		assert(b.size() == bits);

		vector<int> out(bits);

		out[0] = add_xor({a[0], b[0]});
		int carry = add_and({a[0], b[0]});

		for (int i = 1; i < bits; i++) {
			out[i] = add_xor({a[i], b[i], carry});
			carry = add_or({add_and({a[i], b[i]}), add_and({a[i], carry}), add_and({b[i], carry})});
		}

		return out;
	};
	auto add_one = [&](int bits, vector<int> a) {
		assert(a.size() == bits);

		vector<int> out(bits);
		
		out[0] = add_not(a[0]);
		int carry = add_and({a[0]});

		for (int i = 1; i < bits; i++) {
			out[i] = add_xor({a[i], carry});
			carry = add_and({a[i], carry});
		}

		return out;
	};

	// Grid
	vector<vector<int>> grid(H, vector<int>(W));
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			grid[i][j] = i * W + j;

	// Column OR
	vector<int> col(W);
	for (int i = 0; i < W; i++) {
		vector<int> cells;
		for (int j = 0; j < H; j++)
			cells.push_back(grid[j][i]);
		
		col[i] = add_or(cells);
	}

	// Column MASKS
	vector<vector<int>> col_xor(W, vector<int>(bits));
	vector<vector<int>> col_last(W, vector<int>(bits));
	vector<int> found_before_col(W);

	for (int i = 0; i < W; i++) {
		for (int b = 0; b < bits; b++) {
			if ((i >> b) & 1) {
				if (i == 0) {
					col_xor[i][b] = add_and({col[i]});
					col_last[i][b] = add_xor({0, 0}); // Always ZERO
				} else {
					col_xor[i][b] = add_xor({col_xor[i - 1][b], col[i]});
					int temp = add_and({col[i], found_before_col[i - 1]});
					col_last[i][b] = add_or({col_last[i - 1][b], temp});
				}
			} else {
				if (i == 0) {
					col_xor[i][b] = add_xor({0, 0}); // Always ZERO
					col_last[i][b] = add_xor({0, 0}); // Always ZERO
				} else {
					col_xor[i][b] = add_and({col_xor[i - 1][b]});
					col_last[i][b] = add_and({col_last[i - 1][b], found_before_col[i - 1]});
				}
			}
		}

		if (i == 0) {
			found_before_col[i] = add_and({col[i]});
		} else {
			found_before_col[i] = add_or({col[i], found_before_col[i - 1]});
		}
	}

	// Column DISTINCT
	int distinct_col;
	{
		vector<int> cells;
		for (int i = 0; i < W; i++)
			cells.push_back(col[i]);
		distinct_col = add_not(add_xor(cells));
	}

	// Column MATH
	vector<int> neg_col_first(bits);
	for (int i = 0; i < bits; i++) {
		neg_col_first[i] = add_not(add_xor({col_last[W - 1][i], col_xor[W - 1][i]}));
	}

	vector<int> col_pre_diff = add_adder(bits, col_last[W - 1], add_one(bits, neg_col_first));

	vector<int> col_diff(bits);
	for (int i = 0; i < bits; i++) {
		col_diff[i] = add_and({distinct_col, col_pre_diff[i]});
	}

	// Row OR
	vector<int> row(H);
	for (int i = 0; i < H; i++) {
		vector<int> cells;
		for (int j = 0; j < W; j++)
			cells.push_back(grid[i][j]);
		
		row[i] = add_or(cells);
	}

	// Row MASKS
	vector<vector<int>> row_xor(H, vector<int>(bits));
	vector<vector<int>> row_last(H, vector<int>(bits));
	vector<int> found_before_row(H);

	for (int i = 0; i < H; i++) {
		for (int b = 0; b < bits; b++) {
			if ((i >> b) & 1) {
				if (i == 0) {
					row_xor[i][b] = add_and({row[i]});
					row_last[i][b] = add_xor({0, 0}); // Always ZERO
				} else {
					row_xor[i][b] = add_xor({row_xor[i - 1][b], row[i]});
					int temp = add_and({row[i], found_before_row[i - 1]});
					row_last[i][b] = add_or({row_last[i - 1][b], temp});
				}
			} else {
				if (i == 0) {
					row_xor[i][b] = add_xor({0, 0}); // Always ZERO
					row_last[i][b] = add_xor({0, 0}); // Always ZERO
				} else {
					row_xor[i][b] = add_and({row_xor[i - 1][b]});
					row_last[i][b] = add_and({row_last[i - 1][b], found_before_row[i - 1]});
				}
			}
		}

		if (i == 0) {
			found_before_row[i] = add_and({row[i]});
		} else {
			found_before_row[i] = add_or({row[i], found_before_row[i - 1]});
		}
	}

	// Row DISTINCT
	int distinct_row;
	{
		vector<int> cells;
		for (int i = 0; i < H; i++)
			cells.push_back(row[i]);
		distinct_row = add_not(add_xor(cells));
	}

	// Row MATH
	vector<int> neg_row_first(bits);
	for (int i = 0; i < bits; i++) {
		neg_row_first[i] = add_not(add_xor({row_last[H - 1][i], row_xor[H - 1][i]}));
	}

	vector<int> row_pre_diff = add_adder(bits, row_last[H - 1], add_one(bits, neg_row_first));

	vector<int> row_diff(bits);
	for (int i = 0; i < bits; i++) {
		row_diff[i] = add_and({distinct_row, row_pre_diff[i]});
	}

	col_diff.push_back(add_xor({0, 0}));
	row_diff.push_back(add_xor({0, 0}));

	// Total distance
	vector<int> sum = add_adder(bits + 1, col_diff, row_diff);

	// Equality check
	vector<int> diffs(bits + 1);
	for (int i = 0; i <= bits; i++) {
		if ((K >> i) & 1) {
			diffs[i] = add_and({sum[i]});
		} else {
			diffs[i] = add_not(sum[i]);
		}
	}

	add_and(diffs);
}
