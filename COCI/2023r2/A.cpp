#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;

    cin >> n;
    vector<int> times(n);
    string name;
    int t1, t2;
    int mi = INT_MAX, mi1, mi2;
    for (int i = 1; i < n; i++) {
        cin >> name;
        if (name == "Patrik") {
            cin >> t1;
            times[i] = t1;
        } else {
            cin >> t1 >> t2;
            times[i] = times[t1 - 1] + t2;
        }

        if (times[i] - times[i - 1] < mi) {
            mi = times[i] - times[i - 1];
            mi1 = i;
            mi2 = i + 1;
        }

    }

    cout << mi << " " << mi1 << " " << mi2 << endl;

    return 0;
}