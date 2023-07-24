#include <bits/stdc++.h>
using namespace std;

vector<int> coin_flips(vector<int> b, int c) {
    int ret = c;
    for (int i = 0; i < 64; i++) ret ^= (b[i] * i);
    return {ret};
}

int find_coin(vector<int> b) {
    int ret = 0;
    for (int i = 0; i < 64; i++) ret ^= (b[i] * i);
    return ret;
}