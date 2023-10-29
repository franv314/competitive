#include <bits/stdc++.h>
using namespace std;

class Trie {
    struct Node {
        bool is_word;
        int depth;
        Node *children[26];

        Node() : is_word(false), depth(0) {
            fill(children, children + 26, (Node*)NULL);
        }
    } *root;
    vector<char> op;

    void insert(const char *word, int word_size, Node *node) {
        node->depth = max(node->depth, word_size);
        if (*word == '\0') return void(node->is_word = true);
        if (node->children[*word - 'a'] == NULL) {
            node->children[*word - 'a'] = new Node;
        }
        insert(word + 1, word_size, node->children[*word - 'a']);
    }

    void dfs(Node *node) {
        if (node->is_word) op.push_back('P');
        vector<char> ch;
        for (char x = 'a'; x <= 'z'; x++) {
            if (node->children[x - 'a'] != NULL) {
                ch.push_back(x);
            }
        }
        sort(ch.begin(), ch.end(), [&](char a, char b) {
            return node->children[a - 'a']->depth < node->children[b - 'a']->depth;
        });

        for (auto x: ch) {
            op.push_back(x);
            dfs(node->children[x - 'a']);
            op.push_back('-');
        }
    }

public:

    void insert(const char *word, int word_size) { insert(word, word_size, root); }
    vector<char> ops() {
        dfs(root);
        while (!op.empty() && op.back() != 'P') op.pop_back();
        return op;
    }

    Trie() { root = new Node; }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;

    Trie trie;
    for (int i = 0; i < N; i++) {
        string S; cin >> S;
        trie.insert(S.c_str(), S.size());
    }

    vector<char> ans = trie.ops();
    cout << ans.size() << '\n';
    for (auto c: ans) cout << c << '\n';
}