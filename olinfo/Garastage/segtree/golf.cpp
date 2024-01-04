#include<vector>
#define A L l,L r,L n=1,L b=0,L e=1<<20){p(n,b,e);
#define B (int l,int r
#define C l,r,2*n,b,(b+e)/2)
#define D l,r,2*n+1,(b+e)/2,e)
#define X {0,(L)1e9}
#define Y t?f[n]=1,J=x:J+=x,p(n,b,e)
#define E(x,y)if(b>=r||e<=l)G x;if(l<=b&&e<=r)G y;
#define F l,r)
#define G return
#define H void
#define J y[n]
using L=long long;struct I{L s,m;I g(I o){G{s+o.s,m<o.m?m:o.m};}};I s[1<<22];L y[1<<22],f[1<<22],i=1<<20;H p(L n,L b,L e){if(f[n]){s[n].s=(e-b)*(s[n].m=J);y[2*n]=y[2*n+1]=J;f[2*n]=f[2*n+1]=f[n];J=f[n]=0;G;}s[n].m+=J;s[n].s+=(e-b)*J;y[2*n]+=J;y[2*n+1]+=J;J=0;}I g(A
E(X,s[n])G g(C.g(g(D);}H u(L x,L t, A
E(,Y)u(x,t,C;u(x,t,D;s[n]=s[2*n].g(s[2*n+1]);}L k(L x,A
if(b>=r||e<=l||s[n].m>x)G 1e9;if(b+1==e)G b;L z=k(x,C;G z==1e9?k(x,D:z;}H init(std::vector<L>a){for(L x:a)s[i++].s=s[i].m=x;for(i=1<<20;--i;)s[i]=s[2*i].g(s[2*i+1]);}H add B,L x){u(x,0,F;}H set_range B,L x){u(x,1,F;}L get_sum B){G g(F.s;}L get_min B){G g(F.m;}int lower_bound B,L x){L z=k(x,F;G z==1e9?-1:z;}