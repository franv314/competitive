// NOTE: it is recommended to use this even if you don't understand the following code.

#include <iostream>
#include <fstream>
#include <vector>

#define MIN(a,b) (a<b?a:b)

using namespace std;

int main() {
//  uncomment the following lines if you want to read/write from files
//  ifstream cin("input.txt");
//  ofstream cout("output.txt");

    int N;
    cin >> N;

    vector<int> T(N);
    for (int i=0; i<N; i++)
        cin >> T[i];

    int opt_non_posso = 0, opt_posso = 0;
    for (int i = 0; i < N; i++) {
        int temp = opt_non_posso;
        opt_non_posso = opt_posso;
        opt_posso = T[i] + MIN(temp, opt_posso);
    }

    cout << MIN(opt_posso, opt_non_posso) << endl; // print the result                                                                                                                                                   
    return 0;                                                                                                                                                                                 
}  