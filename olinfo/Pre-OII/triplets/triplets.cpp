#include <bits/stdc++.h>
#define MAXN ((int)2e5)
#define _ << " " <<
using namespace std;

struct Node {
    int idx, depth;  
};

vector<int> neighbours[MAXN];

int build(int N, vector<int> A, vector<int> B) {
	for (int i = 0; i < N - 1; i++) {
        neighbours[A[i]].push_back(B[i]);
        neighbours[B[i]].push_back(A[i]);
    }
    Node curr;
    
    vector<int> came_from_fst(N, -1);
    queue<Node> pass1 = {};
    pass1.push({0, 0});
    while (!pass1.empty()) {
        curr = pass1.front();
        pass1.pop();

        for (auto neighbour: neighbours[curr.idx]) {
            if (neighbour != came_from_fst[curr.idx]) {
                pass1.push({neighbour, curr.depth + 1});
                came_from_fst[neighbour] = curr.idx;
            }
        }
    }
    
    vector<int> nodes_to_check;
    vector<int> came_from(N, -1);
    queue<Node> pass2 = {};
    pass2.push({curr.idx, 0});
    while (!pass2.empty()) {
        curr = pass2.front();
        pass2.pop();

        bool leaf = true;
        for (auto neighbour: neighbours[curr.idx]) {
            if (neighbour != came_from[curr.idx]) {
                leaf = false;
                pass2.push({neighbour, curr.depth + 1});
                came_from[neighbour] = curr.idx;
            }
        }
        if (leaf)
            nodes_to_check.push_back(curr.idx);
    }
    int dst = curr.depth;

    unordered_set<int> path;
    for (int c = curr.idx; c != -1; c = came_from[c]) {
        path.insert(c);
    }

    int _max = 0;
    for (auto node: nodes_to_check) {
        int i;
        for (i = 0; path.find(node) == path.end(); node = came_from[node], i++) ;
        _max = max(_max, i);
    }

    return 2 * (dst + _max);
}