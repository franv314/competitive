
// NOTE: it is recommended to use this even if you don't understand the following code.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// input data
int N;
string S;

int main() {
//  uncomment the following lines if you want to read/write from files
//  ifstream cin("input.txt");
//  ofstream cout("output.txt");

    cin >> N;
    cin.ignore();

    int count = 0;

    for (int i=0; i<N; i++) {
        getline(cin, S);
        int d[26] = {};

        for (auto c: S) {
            if ('a' <= c && c <= 'z')
                if (++d[c -'a'] > 2) goto out;
            if ('A' <= c && c <= 'Z')
                if (++d[c -'A'] > 2) goto out;
        }
        count++;
        out:;
    }

    cout << count << endl; // print the result
    return 0;
}