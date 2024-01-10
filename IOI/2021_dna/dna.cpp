#include "dna.h"
#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'000

int ps[MAXN + 1][3][3];

int f(char c) {
	switch (c) {
	case 'T': return 0;
	case 'A': return 1;
	case 'C': return 2;
	}
}

void init(string a, string b) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				ps[i + 1][j][k] = ps[i][j][k];
			}
		}
		ps[i + 1][f(a[i])][f(b[i])]++;
	}
}

int get_distance(int x, int y) {
	y++;

	int aa = ps[y][0][0] - ps[x][0][0];
	int ab = ps[y][0][1] - ps[x][0][1];
	int ac = ps[y][0][2] - ps[x][0][2];
	int ba = ps[y][1][0] - ps[x][1][0];
	int bb = ps[y][1][1] - ps[x][1][1];
	int bc = ps[y][1][2] - ps[x][1][2];
	int ca = ps[y][2][0] - ps[x][2][0];
	int cb = ps[y][2][1] - ps[x][2][1];
	int cc = ps[y][2][2] - ps[x][2][2];

	int sa = aa + ab + ac;
	int sb = ba + bb + bc;
	int sc = ca + cb + cc;

	int ta = aa + ba + ca;
	int tb = ab + bb + cb;
	int tc = ac + bc + cc;

	if (sa != ta || sb != tb || sc != tc) return -1;

	int swaps = min(ab, ba) + min(bc, cb) + min(ac, ca);

	return swaps + (y - x - 2 * swaps - aa - bb - cc) / 3 * 2;
}
