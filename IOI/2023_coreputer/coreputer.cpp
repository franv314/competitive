#include <bits/stdc++.h>
#include "coreputer.h"
using namespace std;

bool is_even = false;

int diag(vector<int> test) {
	int ans = run_diagnostic(test);
	is_even |= (ans == 0);
	return ans;
}

vector<int> malfunctioning_cores(int N) {
	int l = 0, r = N;
	while (l + 1 < r) {
		int m = (l + r) / 2;

		vector<int> test(m);
		iota(test.begin(), test.end(), 0);

		if (diag(test) > 0) r = m;
		else l = m;
	}

	if (l == N - 1) {
		vector<int> ans(N);
		ans[N - 1] = true;

		vector<int> base_test = {N - 1};
		if (is_even) {
			bool found = 0;
			for (int i = N - 2; i > 0; i--) {
				vector<int> test = base_test;
				test.push_back(i);

				if (diag(test) > 0) {
					found = true;
					ans[i] = true;
					break;
				}
			}

			if (!found) ans[0] = true;
		}
		return ans;
	}

	int ch = l;
	vector<int> ans(N);
	ans[ch] = true;

	vector<int> base_test;
	int cnt = 1;

	base_test.resize(N - ch - 1);
	iota(base_test.begin(), base_test.end(), ch + 1);

	for (int i = ch - 1; i >= 0; i--) {
		vector<int> test = base_test;
		test.push_back(i);

		if (diag(test) >= 0) {
			ans[i] = true;
			cnt--;
		}
	}

	base_test.resize(ch);
	iota(base_test.begin(), base_test.end(), 0);

	for (int i = ch + 1; i < N - 1; i++) {
		vector<int> test = base_test;
		test.push_back(i);

		if (diag(test) > 0) {
			ans[i] = true;
			cnt++;
		}
	}

	if ((is_even && cnt == -1) || (!is_even && cnt == 0)) {
		ans[N - 1] = true;
	}

	return ans;
}
