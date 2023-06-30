#include <bits/stdc++.h>
using namespace std;

set<long long> autogrills;

void inizia() { }

void apri(long long p) {
    autogrills.insert(p);
}

void chiudi(long long p) {
    autogrills.erase(p);
}

long long chiedi(long long p) {
    if (autogrills.empty()) return -1;

    auto it1 = autogrills.lower_bound(p);
    if (it1 == autogrills.end()) return *prev(it1);
    if (it1 == autogrills.begin()) return *it1;
    
    auto it2 = prev(it1);
    if (abs(p - *it2) < abs(p - *it1)) return *it2;
    return *it1;
}