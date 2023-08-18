// NOTE: it is recommended to use this even if you don't understand the following code.

#include <bits/stdc++.h>

using namespace std;

struct P {
    int idx;
    int val;

    P(int i, int v) {
        idx = i;
        val = v;
    }
};

vector<P> pp, pm, mp, mm;

bool operator<(P a, P b) { return a.val < b.val; }

int main(){
//  uncomment the following lines if you want to read/write from files
//  ifstream cin("input.txt");
//  ofstream cout("output.txt");

	ios::sync_with_stdio(false);

    int N;
    cin >> N;

	for(int i = 0; i < N; i++) {
        int j;
		cin >> j;
        pp.push_back(P(i, i + j));
        pm.push_back(P(i, i - j));
        mp.push_back(P(i, - i + j));
        mm.push_back(P(i, - i - j));
	}

    sort(pp.begin(), pp.end());
    sort(pm.begin(), pm.end());
    sort(mp.begin(), mp.end());
    sort(mm.begin(), mm.end());

    int res1 = 0, res2 = 0, res3 = 0, res4 = 0;

    if (pp.back().idx >= mm.front().idx && pp.back().val >= mm.front().val) res1 = pp.back().val + mm.back().val;
    if (pm.back().idx >= mp.front().idx && pm.back().val >= mp.front().val) res2 = pm.back().val + mp.back().val;
    if (mp.back().idx >= pm.front().idx && mp.back().val >= pm.front().val) res3 = mp.back().val + pm.back().val;
    if (mm.back().idx >= pp.front().idx && mm.back().val >= pp.front().val) res4 = mm.back().val + pp.back().val;

    // print the result
	cout << max(max(res1, res2), max(res3, res4)) << endl;

	return 0;
}