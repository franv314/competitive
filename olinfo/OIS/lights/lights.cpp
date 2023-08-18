#include <bits/stdc++.h>
using namespace std;

int main(){
int N,C;cin>>N>>C;
vector<int> L(N);
for(int i=0;i<N;i++) cin>>L[i];
map<int,int> am;
int r=0;
int mi=INT_MAX;
for(int l=0;l<N;){
while(am.size()<C && r<N) {
am[L[r]]++;
r++;
}
if(am.size()<C)break;
while(am.size()==C){
if(--am[L[l]]==0) am.erase(L[l]);
l++;
}
mi=min(mi,r-l+1);
if(r==N)break;
}
cout << mi << endl;
}