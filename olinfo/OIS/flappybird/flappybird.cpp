// NOTE: it is recommended to use this even if you don't understand the following code.

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// input data
int N;
vector<int> A, B;

int main() {
//  uncomment the following lines if you want to read/write from files
//  ifstream cin("input.txt");
//  ofstream cout("output.txt");

    cin >> N;
    A.resize(N);
    B.resize(N);
    bool can = true;
    for (int i=0; i<N; i++) {
        cin >> A[i] >> B[i];
        if (i && (A[i] > B[i - 1] || B[i] < A[i - 1])) {
            can = false;
        }
    }

    cout << (can ? "YES" : "NO") << endl; // print the result
    return 0;
}