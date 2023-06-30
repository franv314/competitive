#include <bits/stdc++.h>
using namespace std;

int main() {
    int x; cin >> x;
    vector<int> first_sectors;
    first_sectors.push_back(x);
    
    int ans;
    
    while (first_sectors.size() < 1000) {
        cout << "+ 1" << endl;
        cin >> ans;
        
        if (ans == first_sectors[0]) {
            cout << "! " << first_sectors.size() << endl;
            return 0;
        }
        
        first_sectors.push_back(ans);
    }
    
    cout << "- 999" << endl;
    cin >> ans;
    
    for (int move = 1; ; move++) {
        cout << "+ 1000" << endl;
        cin >> ans;
        
        auto pos = find(first_sectors.begin(), first_sectors.end(), ans);
        if (pos != first_sectors.end()) {
            int p = pos - first_sectors.begin();
            cout << "! " << move * 1000 - p << endl;
            return 0;
        }
    }
}