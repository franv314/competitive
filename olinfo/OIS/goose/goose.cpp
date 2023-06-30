// NOTE: it is recommended to use this even if you don't understand the following code.

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// input data
int N;
vector<int> J;

int main() {
//  uncomment the following lines if you want to read/write from files
//  ifstream cin("input.txt");
//  ofstream cout("output.txt");

    cin >> N;
    J.resize(N);
    for (int i=0; i<N; i++)
        cin >> J[i];

    for (int i=1; i<=6; i++) {
        int pos = 0, count = 0;
        while (pos < N) {
            count++;
            pos += i;
            while (J[pos] && pos < N) pos += J[pos];
        }
        cout << count << " ";
    }
    cout << endl;
    return 0;
}
