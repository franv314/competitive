// NOTE: it is recommended to use this even if you don't understand the
// following code.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// input data
int N;
string S;

int main() {
    //  uncomment the following lines if you want to read/write from files
    //  ifstream cin("input.txt");
    //  ofstream cout("output.txt");

    cin >> N;
    cin >> S;

    char c[128];
    c['q'] = 'w';
    c['w'] = 'e';
    c['e'] = 'r';
    c['r'] = 't';
    c['t'] = 'y';
    c['y'] = 'u';
    c['u'] = 'i';
    c['i'] = 'o';
    c['o'] = 'p';
    c['a'] = 's';
    c['s'] = 'd';
    c['d'] = 'f';
    c['f'] = 'g';
    c['g'] = 'h';
    c['h'] = 'j';
    c['j'] = 'k';
    c['k'] = 'l';
    c['z'] = 'x';
    c['x'] = 'c';
    c['c'] = 'v';
    c['v'] = 'b';
    c['b'] = 'n';
    c['n'] = 'm';

    string s = "";
    for (auto x:S) s+=c[x];
    // insert your code here

    cout << s << endl; // print the result
    return 0;
}