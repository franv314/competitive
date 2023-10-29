#include "aplusb.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> smallest_sums(int N, vector<int> A, vector<int> B) {
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	int64_t l = 0, r = 2e9 + 10;
	while (l + 1 < r) {
		int64_t m = (l + r) / 2;

		int64_t total = 0;
		for (auto a: A) {
			total += upper_bound(B.begin(), B.end(), m - a) - B.begin();
		}

		if (total <= N) l = m;
		else r = m;
	}

	vector<int> ans;
	ans.reserve(N);

	for (auto a: A) {
		auto last = upper_bound(B.begin(), B.end(), l - a);
		for (auto it = B.begin(); it != last; it++) {
			ans.push_back(a + *it);
		}
	}

	sort(ans.begin(), ans.end());
	while (ans.size() < N) ans.push_back(r);

	return ans;
}
