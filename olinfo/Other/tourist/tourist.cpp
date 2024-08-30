#include <bits/stdc++.h>
using namespace std;

int GreatestHappiness(int N, int K, int *C) {
    int happy = 0, ans = 0;
    priority_queue<int, vector<int>, greater<int>> values;

    for (int i = 0; i < N; i++) {
        happy += C[i];
        values.push(C[i]);
        while (values.size() > K - i) {
            happy -= values.top();
            values.pop();
        }

        ans = max(ans, happy);
    }

    return ans;
}
