// NOTE: it is recommended to use this even if you don't understand the following code.

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// input data
int N;
vector<int> V, S;

int main() {
//  uncomment the following lines if you want to read/write from files
//  ifstream cin("input.txt");
//  ofstream cout("output.txt");

    cin >> N;
    V.resize(N);
    S.resize(N);
    for (int i=0; i<N; i++)
        cin >> V[i];
    for (int i=0; i<N; i++)
        cin >> S[i];

    long long res = 0;
    long long sum = 0;
    int last = -1;
    for (int i = 0; i < N; i++) {
        if (S[i]) {
            if (V[i] >= last)
                sum += (last = V[i]);
            else {
                if (sum > res) res = sum;
                sum = last = V[i];
            }
        } else {
            if (sum > res) res = sum;
            sum = 0;
            last = -1;
        }
    }
    if (sum > res) res = sum;
    cout << res << endl; // print the result
    return 0;
}