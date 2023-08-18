#include <bits/stdc++.h>
using namespace std;

// constraints
#define MAXN 100000
// input data
int N1, N2, i;
int ID1[MAXN], ID2[MAXN];

set<int> ONE, TWO, INT;

int main() {
//  uncomment the following lines if you want to read/write from files
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

    assert(2 == scanf("%d %d", &N1, &N2));
    for(i=0; i<N1; i++)
        assert(1 == scanf("%d", &ID1[i]));
    for(i=0; i<N2; i++)
        assert(1 == scanf("%d", &ID2[i]));
    
    for(i=0; i<N1; i++)
        ONE.insert(ID1[i]);
    for(i=0; i<N2; i++)
        TWO.insert(ID2[i]);

    for (auto x: ONE)
        if (TWO.find(x) != TWO.end())
            INT.insert(x);
            
    for (auto x: TWO)
        if (ONE.find(x) != ONE.end())
            INT.insert(x);
    

    // insert your code here
    
    printf("%lu\n", INT.size()); // print the result
    return 0;
}