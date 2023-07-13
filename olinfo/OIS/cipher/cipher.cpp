#include <bits/stdc++.h>
using namespace std;

#define SIGMA 26
#define MAXL 400'001

class Trie {
    struct Node {
        int idx;
        array<Node*, SIGMA> children;

        Node() : idx(0) {
            children.fill(NULL);
        }
    } *root;
    
    void add(const char *str, int str_idx, Node *node) {
        if (*str == '\0') return void(node->idx = node->idx ?: str_idx);
        int child = *str - 'a';
        if (node->children[child] == NULL) node->children[child] = new Node();
        add(str + 1, str_idx, node->children[child]);
    }
    
    int get_min(const char *str, Node *node) {
        if (node->idx) return node->idx;
        assert(any_of(node->children.begin(), node->children.end(), [&](Node *a){ return a != NULL; }));
        int val = *str - 'a';
        int c = 0;
        for (int att = (SIGMA - val) % SIGMA; ; att = (att + 1) % SIGMA) {
            if (node->children[att] != NULL) {
                return get_min(str + 1, node->children[att]);
            }
        }
    }
    
public:
    
    void add(const char *str, int str_idx) { add(str, str_idx, root); }
    int get_min(const char *str) { return get_min(str, root); }
    Trie() { root = new Node(); }
};

bitset<MAXL> any_string;
Trie tries[MAXL];

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int N, K; cin >> N >> K;
    vector<string> T(K), S(N);
    
    for (auto &t: T) cin >> t;
    for (auto &s: S) cin >> s;

    for (int i = 0; i < K; i++) {
        any_string.set(T[i].size());
        tries[T[i].size()].add(T[i].c_str(), i + 1);
    }

    string encrypted;
    for (auto s: S) {
        pair<string, int> mi = {"~", -1};
        encrypted.resize(s.size());

        vector<int> divisors;
        for (int i = 1; i * i <= s.size(); i++) {
            if (s.size() % i) continue;
            divisors.push_back(i);
            divisors.push_back(s.size() / i);
        }

        for (auto len: divisors) {
            if (!any_string.test(len)) continue;

            int mi_idx = tries[len].get_min(s.c_str()) - 1;
            string mi_str = T[mi_idx];

            for (int i = 0; i < s.size(); i++) {
                encrypted[i] = (s[i] - 'a' + mi_str[i % len] - 'a') % SIGMA + 'a';
            }
            mi = min(mi, {encrypted, mi_idx + 1});
        }
        cout << mi.second << '\n';
    }
}