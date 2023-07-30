#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    string S; cin >> S;
    
    set<int> existing;
    for (int i = 0; i <= N; i++) existing.insert(i);
    
    int alice_next = 0, bob_next = 0;
    for (int i = 1; i <= N; i++) {
        if (i & 1) {
            while (alice_next <= N && S[alice_next] == 'A') alice_next++;
            existing.erase(alice_next++);
        } else {
            while (bob_next <= N && S[bob_next] == 'B') bob_next++;
            existing.erase(bob_next++);
        }
        int mex = *existing.begin();
        
        if (S[mex] == 'A') cout << "Alice\n";
        else cout << "Bob\n";
    }
}