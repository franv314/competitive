// NOTE: it is recommended to use this even if you don't understand the
// following code.

#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")

using namespace std;

int div_(int a, int b) {
	if (a == 0 && b == 0) return 0b111;
	if (a == b) return 0b100;
	if (a == 2*b) return 0b010;
	if (2*a == b) return 0b001;
	return 0b000;
}

typedef vector<pair<int, int>> Song;

pair<bool, int> ev_seq(pair<Song, Song> seqs) {
	bool direct = true, inverse = true;
	int _div, diff;
	int size = seqs.first.size();
	
	_div = div_(seqs.second[0].first, seqs.first[0].first);
	diff = seqs.second[0].second - seqs.first[0].second;
	for (int i = 0; i < size; i++) {
		if ((seqs.second[i].second - seqs.first[i].second != diff) ||
			!(div_(seqs.second[i].first, seqs.first[i].first) & _div)) {
				direct = false;
				break;
		}
	}

	_div = div_(seqs.second[0].first, seqs.first[size - 1].first);
	diff = seqs.second[0].second - seqs.first[size - 1].second;
	for (int i = 0; i < size; i++) {
		if ((seqs.second[i].second - seqs.first[size - i - 1].second != diff) ||
			!(div_(seqs.second[i].first, seqs.first[size - i - 1].first) & _div)) {
				inverse = false;
				break;
		}
	}
		
	return {direct || inverse, size};
}

void solve(Song x, Song y) {
	pair<Song, Song> seqs = {};
	for (int i = 0; i < x.size(); i++) {
		if (x[i] != y[i]) {
			seqs.first.push_back(x[i]);
			seqs.second.push_back(y[i]);
		}
	}
	if (seqs.first.empty()) {
		cout << "SAME" << endl;
		return;
	}
	
	auto res = ev_seq(seqs);
	if (res.first) cout << "TRANSFORMED " << res.second << endl;
	else cout << "ORIGINAL " << res.second << endl;
}

// input data
int N, V;
Song X, Y;

int main() {
    //  uncomment the following lines if you want to read/write from files
        ifstream cin("input.txt");
    //  ofstream cout("output.txt");

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> V;
    X.resize(N);
    Y.resize(N);
    for (auto &x : X) {
        cin >> x.first >> x.second;
    }
    for (auto &y : Y) {
        cin >> y.first >> y.second;
    }

	solve(X, Y);
    return 0;
}