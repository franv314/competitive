#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

vector<bitset<12>> sets;

void init() {
    for (int i = 0; i < (1 << 12); i++) {
        if (__builtin_popcount(i) == 6) {
            sets.emplace_back(i);
        }
    }
}

void encode() {
    int N, T; cin >> N >> T;
    while (T--) {
        int x, y; cin >> x >> y;
        
        for (int i = 0; i < 12; i++) {
            if (sets[x].test(i) && !sets[y].test(i)) {
                cout << i + 1 << '\n';
                break;
            }
        }
    }
}

void decode() {
    int N, T; cin >> N >> T;
    while (T--) {
        int x, h; cin >> x >> h;
        
        cout << (sets[x].test(h - 1) ? "yes\n" : "no\n");
    }
}

int main() {
    init();
    
    int type; cin >> type;
    if (type == 1) {
        encode();
    } else {
        decode();
    }
}