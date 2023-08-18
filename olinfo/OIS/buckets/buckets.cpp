// NOTE: it is recommended to use this even if you don't understand the following code.

#include <bits/stdc++.h>

using namespace std;

// input data
int N, i;
vector<int> D;

int main() {
//  uncomment the following lines if you want to read/write from files
//  ifstream cin("input.txt");
//  ofstream cout("output.txt");

    cin >> N;
    D.resize(N);
    for (int i=0; i<N; i++)
        cin >> D[i];
        
    sort(D.begin(), D.end());
    for (int i = 0; i < N - 1; i++)
        if (D[i]==D[i+1]) {
            cout << "Impossible";
            return 0;
        }
                                                                                                                                                                                              
    cout << "Ok"; // print the result                                                                                                                                                           
    return 0;                                                                                                                                                                                 
} 