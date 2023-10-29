#include <bits/stdc++.h>
#include "lockpicking.h"
using namespace std;

int N;
vector<int> B;
vector<vector<int>> T;

int build(vector<int> states, int depth = 0) {
	if (states.size() == 1 || depth == N) {
		return states[0];
	}

	int ex_0 = 0, ex_1 = 0;
	for (auto state: states) {
		if (B[state]) ex_1++;
		else ex_0++;
	}

	int out = ex_1 > ex_0;
	vector<int> a, b;
	for (auto state: states) {
		if (B[state] == out) a.push_back(T[state][out]);
		else b.push_back(T[state][out]);
	}

	int st_1 = a.empty() ? 0 : build(a, depth + 1);
	int st_2 = b.empty() ? 0 : build(b);

	B.push_back(out);
	if (!out) T.push_back({st_1, st_2});
	else T.push_back({st_2, st_1});

	return B.size() - 1;
}

void construct_card(int N, vector<int> A, vector<vector<int>> S) {
	::N = N;
	B = A;
	T = S;

	vector<int> st(N);
	iota(st.begin(), st.end(), 0);
	int j0 = build(st);

	define_states(B.size(), B, T, j0);
}