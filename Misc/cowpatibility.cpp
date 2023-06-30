#include <bits/stdc++.h>
using namespace std;

namespace std {
    template<>
    struct hash<array<int, 5>> {
        size_t operator()(array<int, 5> a) const {
            hash<int> h;
            return h(a[0]) + 129487 * h(a[1]) + 4958 * h(a[2]) + 34878 * h(a[3]) + 129849 * h(a[4]);
        }
    };
}

ifstream in("cowpatibility.in");
ofstream out("cowpatibility.out");

int main() {
    int N; in >> N;
    int total_cowpatibilities = 0;
    
    unordered_map<array<int, 5>, int> cnt;
    array<int, 5> val;
    array<int, 5> flavors;
    
    for (int i = 0; i < N; i++) {
        for (auto &flavor: flavors) {
            in >> flavor;
        }
        sort(flavors.begin(), flavors.end());
        
        int cowpatibilities = 0;
        for (int mask = 1; mask < 32; mask++) {
            int k = 0;
            for (int j = 0; j < 5; j++) {
                if ((1 << j) & mask) {
                    val[k] = flavors[j];
                    k++;
                }
            }
            while (k < 5) val[k++] = -1;
            if (__builtin_popcount(mask) & 1) cowpatibilities += cnt[val];
            else cowpatibilities -= cnt[val];
            
            cnt[val]++;
        }
        total_cowpatibilities += cowpatibilities;
    }
    
    out << (long long)N * (N - 1) / 2 - total_cowpatibilities;
}