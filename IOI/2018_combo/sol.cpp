#include <bits/stdc++.h>
#include "combo.h"
using namespace std;

array<char, 3> order(char fst) {
    switch (fst) {
    case 'A': return {'B', 'X', 'Y'};
    case 'B': return {'A', 'X', 'Y'};
    case 'X': return {'A', 'B', 'Y'};
    case 'Y': return {'A', 'B', 'X'};
    }
}

string guess(int N, char fst) {
    string curr(1, fst);
    auto [x, y, z] = order(fst);
    
    if (N == 1)
        return curr;

    for (int i = 1; i < N - 1; i++) {
        string query = (curr + x + x) + (curr + x + y) + (curr + x + z) + (curr + y);
        
        switch (press(query) - i) {
        case 0: curr += z; break;
        case 1: curr += y; break;
        case 2: curr += x; break;
        }
    }

    if (press(curr + x) == N)
        return curr + x;
    if (press(curr + y) == N)
        return curr + y;
    return curr + z;
}

string guess_sequence(int N) {
    if (press("AB") != 0) {
        if (press("A") != 0)
            return guess(N, 'A');
        else
            return guess(N, 'B');
    } else {
        if (press("X"))
            return guess(N, 'X');
        else
            return guess(N, 'Y');
    }
}
