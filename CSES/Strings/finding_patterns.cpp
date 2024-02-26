#include <bits/stdc++.h>
using namespace std;

class AhoCorasick {
    struct Node {
        int visits;
        optional<bool> count;

        array<Node*, 26> trans;
        Node* suff;
        vector<Node*> inv;

        Node() : visits(0), suff(NULL) {
            fill(trans.begin(), trans.end(), (Node*)NULL);
        }
    };

    Node* root;
    vector<Node*> dict;

    Node* insert(const string &s) {
        Node* curr = root;
        for (auto c: s) {
            if (!curr->trans[c - 'a']) curr->trans[c - 'a'] = new Node;
            curr = curr->trans[c - 'a'];
        }

        return curr;
    }

    void get_suffixes() {
        queue<Node*> q;
        
        for (int i = 0; i < 26; i++) {
            if (root->trans[i]) {
                root->trans[i]->suff = root;
                root->inv.push_back(root->trans[i]);
                q.push(root->trans[i]);
            } else {
                root->trans[i] = root;
            }
        }

        while (!q.empty()) {
            Node* curr = q.front(); q.pop();

            for (int i = 0; i < 26; i++) {
                if (curr->trans[i]) {
                    curr->trans[i]->suff = curr->suff->trans[i];
                    curr->trans[i]->suff->inv.push_back(curr->trans[i]);
                    q.push(curr->trans[i]);
                } else {
                    curr->trans[i] = curr->suff->trans[i];
                }
            }
        }
    }

public:

    vector<bool> solve(const string &s) {
        Node* curr = root;
        curr->visits++;

        for (auto c: s) {
            curr = curr->trans[c - 'a'];
            curr->visits++;
        }

        auto find = [&](auto &&find, Node* node) {
            if (node->count) return;
            node->count = (bool)node->visits;

            for (auto x: node->inv) {
                find(find, x);
                node->count.value() |= x->count.value();
            }
        };

        vector<bool> found(dict.size());
        for (int i = 0; i < dict.size(); i++) {
            find(find, dict[i]);
            found[i] = dict[i]->count.value();
        }

        return found;
    }

    AhoCorasick(const vector<string> &dictionary) {
        root = new Node;
        for (auto &word: dictionary) {
            dict.push_back(insert(word));
        }
        get_suffixes();
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    string s; cin >> s;
    int k; cin >> k;
    vector<string> dict(k);
    for (auto &x: dict) cin >> x;

    AhoCorasick aho_corasick(dict);
    vector<bool> ans = aho_corasick.solve(s);

    for (auto x: ans) {
        cout << (x ? "YES\n" : "NO\n");
    }
}