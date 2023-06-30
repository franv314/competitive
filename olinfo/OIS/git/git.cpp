#include <bits/stdc++.h>
using namespace std;

struct Node {
    string name;
    bool full;
    bool alr_printed;
    vector<Node*> children;

    Node(string s, bool b) : name(s), full(b), alr_printed(false) {}
};

int N;
bool M;
string P;

void print_dfs(Node *node) {
    if (node->alr_printed) return;
    node->alr_printed = true;

    if (node->full) {
        string p = node->name.back() == '/' ? node->name.substr(0, node->name.size() - 1) : node->name;
        cout << p << endl;
    } else {
        for (auto child: node->children) {
            print_dfs(child);
        }
    }
}

void dfs(Node *node) {
    if (!node->children.empty()) node->full = true;

    for (auto child: node->children) {
        dfs(child);
        if (!child->full) node->full = false;
    }

    if (!node->full) {
        for (auto child: node->children) {
            print_dfs(child);
        }
    }
}

int main() {
    map<string, Node*> nodes;
    nodes["/"] = new Node("/", false);

    cin >> N;
    while (N--) {
        cin >> M >> P;
        string temp, old;
        for (auto c: P) {
            temp += c;
            if (c == '/') {
                if (nodes.find(temp) == nodes.end()) {
                    nodes[temp] = new Node(temp, false);
                    nodes[old]->children.push_back(nodes[temp]);
                }
                old = temp;
            }
        }
        nodes[P] = new Node(P, M);
        nodes[old]->children.push_back(nodes[P]);
    }

    dfs(nodes["/"]);
    if (nodes["/"]->full) cout << "/" << endl;

    return 0;
}