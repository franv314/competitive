#include <bits/stdc++.h>
using namespace std;

vector<int> up;
vector<int> down;

void permute(int subtask, int N, int V[], int R[])
{
    for (int i = 0; i < N; i++) {
        up.push_back(V[i]);
        down.push_back(V[i]);
    }
    sort(up.begin(), up.end());
    sort(down.begin(), down.end());
    reverse(down.begin(), down.end());
    
    for (int i = 0; i < N; i+=2) {
        R[i] = up.back();
        R[i+1] = down.back();
        up.pop_back();
        down.pop_back();
    }
}