#include <bits/stdc++.h>
using namespace std;

struct Elem {
	long unsigned value;
	int index;
};

bool operator<(Elem a, Elem b) { return a.value < b.value; }

int N, M, t;
vector<Elem> eso;
vector<long unsigned> a;
string s;

int main() {
	hash<string> h;

	ifstream cin("input.txt");
	ofstream cout("output.txt");
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		vector<vector<long unsigned>> parents;
		for (int j = 0; j < M; j++) {
			cin >> t;
			switch (t) {
				case -1: case -3:
					parents.push_back({});
					break;
				case -2:
					a = parents.back();
					parents.pop_back();
					sort(a.begin(), a.end());
					s = "";
					for (auto x: a) s += to_string(x);
					if (parents.empty()) eso.push_back({h(s), i});
					else parents.back().push_back(h(s));
					break;
				case -4:
					a = parents.back();
					parents.pop_back();
					if (a.front() > a.back()) reverse(a.begin(), a.end());
					s = "";
					for (auto x: a) s += to_string(x);
					if (parents.empty()) eso.push_back({h(s), i});
					else parents.back().push_back(h(s));
					break;
				default:
					parents.back().push_back(t);
			}
		}
	}
	sort(eso.begin(), eso.end());
	long unsigned old = 0;
	vector<int> breaks = {};
	for (int i = 0; i < eso.size(); i++) {
		if (eso[i].value != old) {
			breaks.push_back(i);
			old = eso[i].value;
		}
	}
	breaks.push_back(eso.size());
	
	cout << breaks.size() - 1 << endl;
	for (int i = 0; i < breaks.size() - 1; i++) {
		cout << breaks[i+1]-breaks[i] << " ";
		for (int j = breaks[i]; j < breaks[i+1]; j++) {
			cout << eso[j].index + 1 << " ";
		}
		cout << endl;
	}
	
	
	return 0;
}