// NOTE: it is recommended to use this even if you don't understand the following code.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	// uncomment the following lines if you want to read/write from files
	// ifstream cin("input.txt");
	// ofstream cout("output.txt");

    int N;
    cin >> N;

    vector<int> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }

    sort(S.begin(), S.end());
    int curr = 0;
    long long total = 0;
    int old = -1;
    for (auto x: S) {
        if (x != old) {
            old = x;
            curr++;
        }
        total += curr;
    }

    cout << total
 << endl; // print the result
    return 0;
}