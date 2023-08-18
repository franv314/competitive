// NOTE: it is recommended to use this even if you don't understand the following code.

#include <bits/stdc++.h>
using namespace std;

// constraints
#define MAXN 400000

using namespace std;

// input data
int N, K, T, i, t;
vector<int> P;

int main() {
    //  uncomment the following lines if you want to read/write from files
    //  freopen("input.txt", "r", stdin);
    //  freopen("output.txt", "w", stdout);

    cin >> T;
    for(t = 0; t < T; t++) {
        cin >> N >> K;
        P.resize(N);
        for(i = 0; i < N; i++) {
            cin >> P[i];
        }
        
        stack<int> s;
        for (auto p: P) {
            if (s.size() && s.top() == p) {
                s.pop();
            } else {
                s.push(p);
            }
        }
        cout << s.empty() << endl;
        
    }
    return 0;
}