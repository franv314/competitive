#include <bits/stdc++.h>
using namespace std;

int main() {
    int size;
    cin >> size;
    
    int sum = 0;
    for (int _ = 0; _ < size; _++) {
        int a;
        cin >> a;
        sum += a;
    }
    cout << sum << " " << (sum * 1.0) / size;
}