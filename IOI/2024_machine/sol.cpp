#include "machine.h"
#include <bits/stdc++.h>
using namespace std;

#define BITS 8

vector<int> find_permutation(int N) {
	vector<int> count(BITS);

	for (int i = 0; i <= N + 2; i++) {
		for (int b = 0; b < BITS; b++) {
			count[b] += (i >> b) & 1;
		}
	}

	int ex1, ex2, ex3;
	for (ex1 = 0; ex1 <= N + 2; ex1++) {
		for (ex2 = 0; ex2 < ex1; ex2++) {
			for (ex3 = 0; ex3 < ex2; ex3++) {
				for (int b = 0; b < BITS; b++) {
					int cnt = count[b] - ((ex1 >> b) & 1) - ((ex2 >> b) & 1) - ((ex3 >> b) & 1);
					if (cnt == N / 2) {
						goto skip;
					}
				}

				goto done;
				skip:;
			}
		}
	}

	done:

	for (int b = 0; b < BITS; b++) {
		count[b] -= ((ex1 >> b) & 1) + ((ex2 >> b) & 1) + ((ex3 >> b) & 1);
	}

	vector<int> q;
	for (int i = 0; i <= N + 2; i++)
		if (i != ex1 && i != ex2 && i != ex3)
			q.push_back(i);

	vector<int> ans = use_machine(q);

	vector<int> ncount(BITS);
	for (auto x: ans) {
		for (int b = 0; b < BITS; b++) {
			ncount[b] += (x >> b) & 1;
		}
	}

	int X = 0;
	for (int b = 0; b < BITS; b++) {
		if (ncount[b] != count[b])
			X |= (1 << b);
	}

	for (auto &x: ans) x ^= X;

	vector<int> ret(N);
	for (int i = 0; i < N; i++) {
		ret[i] = find(q.begin(), q.end(), ans[i]) - q.begin();
	}

	return ret;
}
