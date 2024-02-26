#include <bits/stdc++.h>
using namespace std;

class AhoCorasick {
    struct Node {
        int visits;
        optional<int> pos;

        array<Node*, 26> trans;
        Node* suff;
        vector<Node*> inv;

        Node() : visits(-1), suff(NULL) {
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

    vector<int> solve(const string &s) {
        Node* curr = root;
        curr->visits = 0;

        for (int i = 0; i < s.size(); i++) {
            curr = curr->trans[s[i] - 'a'];
            if (curr->visits == -1) curr->visits = i + 1;
        }

        auto find = [&](auto &&find, Node* node) {
            if (node->pos) return;
            node->pos = node->visits;

            for (auto x: node->inv) {
                find(find, x);
                if (x->pos.value() != -1) {
                    if (node->pos.value() == -1) node->pos.value() = x->pos.value();
                    else node->pos.value() = min(node->pos.value(), x->pos.value());
                }
            }
        };

        vector<int> ans(dict.size());
        for (int i = 0; i < dict.size(); i++) {
            find(find, dict[i]);
            ans[i] = dict[i]->pos.value();
        }

        return ans;
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
    vector<int> ans = aho_corasick.solve(s);

    for (int i = 0; i < k; i++) {
        if (ans[i] == -1) cout << -1 << '\n';
        else cout << ans[i] - dict[i].size() + 1 << '\n';
    }
}