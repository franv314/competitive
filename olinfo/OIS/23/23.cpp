/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.
 * NOTE: it is recommended to use this even if you don't
 * understand the following code.
 */

#include <bits/stdc++.h>
using namespace std;
// constraints
#define MAXT 10000

// input data
int T, i;
vector<int> N, M;
map<int, int> res;

int main() {
//  uncomment the following lines if you want to read/write from files
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

    cin >> T;
    N.resize(T);
    M.resize(T);
    for(i=0; i<T; i++) {
        cin >> N[i];
        M[i] = N[i];
    }
    sort(N.begin(), N.end());
    reverse(N.begin(), N.end());
    
    int i = 1, sp = 0, sum2 = 0, sum3 = 0;
    while (!N.empty()) {
        sp += sum2 == sum3;
        while (i == N.back()) {
            res[i] = sp;
            N.pop_back();
        }
        for (int j = i; j % 2 == 1; j /= 2) sum2--;
        for (int j = i; j % 3 == 2; j /= 3) sum3-=2;
        i++; sum2++; sum3++;
    }
    
    for (auto x: M) cout << res[x] << " ";
    cout << endl;
}