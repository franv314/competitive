#include <bits/stdc++.h>
using namespace std;

bool K() {
    cout << "K" << endl;
    bool k;
    cin >> k;
    return k;
}

void L() {cout << "L" << endl;}
void D() {cout << "D" << endl;}
void X() {cout << "X" << endl;}

int tot;

void dfs() {
    X();
    tot++;
    for (int i = 0; i < 4; i++) {
        if (K()) {
            L(); L(); K(); L(); L();
        } else {
            dfs();
        }
        L();
    }
}

int main() {
    dfs();
    
    cout << tot;

    return 0;
}