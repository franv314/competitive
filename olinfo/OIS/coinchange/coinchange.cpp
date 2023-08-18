/*
 * NOTE: it is recommended to use this even if you don't
 * understand the following code.
 */

#include <fstream>
#include <iostream>

using namespace std;

// input data
long long V[15];

int main() {
//  uncomment the following lines if you want to read/write from files
//  ifstream cin("input.txt");
//  ofstream cout("output.txt");

    for (int i = 0; i < 15; i++)
        cin >> V[i];

    long long sol[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    long long sum = V[0] + 2 * V[1] + 5 * V[2]
                    + 10 * V[3] + 20 * V[4] + 50 * V[5]
                    + 100 * V[6] + 200 * V[7] + 500 * V[8]
                    + 1000 * V[9] + 2000 * V[10] + 5000 * V[11]
                    + 10000 * V[12] + 20000 * V[13] + 50000 * V[14];
    
    sol[14] = sum / 50000; sum -= 50000 * sol[14];
    sol[13] = sum / 20000; sum -= 20000 * sol[13];
    sol[12] = sum / 10000; sum -= 10000 * sol[12];
    
    sol[11] = sum / 5000; sum -= 5000 * sol[11];
    sol[10] = sum / 2000; sum -= 2000 * sol[10];
    sol[9] = sum / 1000; sum -= 1000 * sol[9];
    
    sol[8] = sum / 500; sum -= 500 * sol[8];
    sol[7] = sum / 200; sum -= 200 * sol[7];
    sol[6] = sum / 100; sum -= 100 * sol[6];
    
    sol[5] = sum / 50; sum -= 50 * sol[5];
    sol[4] = sum / 20; sum -= 20 * sol[4];
    sol[3] = sum / 10; sum -= 10 * sol[3];
    
    sol[2] = sum / 5; sum -= 5 * sol[2];
    sol[1] = sum / 2; sum -= 2 * sol[1];
    sol[0] = sum / 1; sum -= 1 * sol[0];

    for (int i = 0; i < 15; i++)
        cout << sol[i] << " ";
    cout << endl;
    return 0;
}