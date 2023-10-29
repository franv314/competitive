#include <bits/stdc++.h>
#include "choreography.h"
using namespace std;

int N;

struct Perm : vector<int64_t> {
	int64_t lazy_even = 0, lazy_odd = 0;
	int64_t offset = 0;

	void rotate(int k) {
		offset += k;
	}

	void add(int k) {
		lazy_even += k;
		lazy_odd += k;
	}

	void invert() {
		if (lazy_even & 1) {
			lazy_even += (N - 1);
			lazy_odd += 1;
		} else {
			lazy_even += 1;
			lazy_odd += (N - 1);
		}
	}

	int get(int pos) {
		int64_t val = (*this)[(pos + offset) % (N / 2)];
		if (val & 1) return (val + lazy_odd) % N;
		return (val + lazy_even) % N;
	}
};

Perm even_dir, odd_dir;
Perm even_inv, odd_inv;

void init(int N, vector<int> P) {
	::N = N;
	even_dir.resize(N / 2);
	odd_dir.resize(N / 2);
	even_inv.resize(N / 2);
	odd_inv.resize(N / 2);

	for (int i = 0; i < N; i++) {
		if (i & 1) odd_dir[i / 2] = P[i];
		else even_dir[i / 2] = P[i];

		if (P[i] & 1) odd_inv[P[i] / 2] = i;
		else even_inv[P[i] / 2] = i;
	}
}

void move_right(int K) {
	even_dir.rotate((N - K + 1) / 2);
	odd_dir.rotate((N - K) / 2);

	if (K & 1) swap(even_dir, odd_dir);

	even_inv.add(K);
	odd_inv.add(K);
}

void move_left(int K) {
	move_right(N - K);
}

void swap_places() {
	swap(even_dir, odd_dir);

	even_inv.invert();
	odd_inv.invert();
}

void move_around() {
	swap(even_dir, even_inv);
	swap(odd_dir, odd_inv);
}

int get_position(int D) {
	if (D & 1) return odd_inv.get(D / 2);
	return even_inv.get(D / 2);
}
