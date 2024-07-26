#include "september.h"
#include <bits/stdc++.h>
using namespace std;

int solve(int N, int M, vector<int> F, vector<vector<int>> S) {
	vector<vector<int>> adj(N);
	for (int i = 1; i < N; i++)
		adj[F[i]].push_back(i);
	
	vector<int> inv_S(N);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N - 1; j++) {
			inv_S[S[i][j]] = max(inv_S[S[i][j]], j);
		}
	}

	vector<bool> visited(N);
	auto dfs = [&](auto &&dfs, int node) -> int {
		if (visited[node])
			return -1;
		visited[node] = true;
		
		int ans = inv_S[node];
		for (auto x: adj[node])
			ans = max(ans, dfs(dfs, x));
		
		return ans;
	};

	int curr_l = 0, k = 0;
	while (curr_l != N - 1) {
		k++;
		
		int curr_r = curr_l + 1;
		for (; curr_l < curr_r; curr_l++) {
			for (int i = 0; i < M; i++) {
				curr_r = max(curr_r, dfs(dfs, S[i][curr_l]) + 1);
			}
		}
	}

	return k;
}
