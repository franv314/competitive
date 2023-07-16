#include <bits/stdc++.h>
using namespace std;

enum Type { LEFT, PASSING, RIGHT };

variant<bool, vector<int>> find_tour(int N, vector<int> A) {
    if (A.front() != 2 || A.back() != 2) return false;
    
    vector<Type> type(N);
    int open = 2;
    type[0] = LEFT;
    
    for (int i = 1; i < N; i++) {
        if (A[i] == open + 2) {
            type[i] = LEFT;
            open += 2;
        } else if (A[i] == open) {
            type[i] = RIGHT;
            open -= 2;
        } else if (A[i] == open + 1) {
            type[i] = PASSING;
        } else {
            return false;
        }
    }
    
    vector<int> ans;
    queue<int> opens;
    ans.push_back(0);
    for (int i = 1; i < N - 1; i++) {
        if (type[i] == LEFT) {
            opens.push(i);
        } else if (type[i] == PASSING) {
            ans.push_back(i);
        } else {
            if (opens.empty()) return false;
            ans.push_back(i);
            ans.push_back(opens.front()); opens.pop();
        }
    }
    assert(opens.empty());
    ans.push_back(N - 1);
    return ans;
}