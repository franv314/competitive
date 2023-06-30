#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    char query;
    uint64_t num;
    cin >> q;
    
    unordered_set<uint64_t> my_set = {0};
    while (q--) {
        cin >> query >> num;
        if (query == '+') my_set.insert(num);
        else if (query == '?') {
            uint64_t div = 0;
            for (; my_set.find(div) != my_set.end(); div += num);
            cout << div << "\n";
        }
    } 

    return 0;
}