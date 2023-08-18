/*
 * NOTE: it is recommended to use this even if you don't
 * understand the following code.
 */

#include <bits/stdc++.h>

using namespace std;

// constraints
#define MAXN 300000

// input data
int N;
vector<int> P;

int main() {
//  uncomment the following lines if you want to read/write from files
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

    cin >> N;
    P.resize(N);
    for(int i = 0; i < N; i++)
        cin >> P[i];

    // insert your code here
    sort(P.begin(),P.end());
    reverse(P.begin(),P.end());
    
    int sum = accumulate(P.begin(),P.end(),0);
    for (int i = 2; i  < N; i+=3) {
        sum -= P[i];
    }
    
    cout << sum << endl; // print the result
    return 0;
}