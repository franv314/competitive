i=input
n=-int(i())
a=sorted(map(int,i().split()))
t=sum(a)
c=10**18
for b in a:
    c=min(c,n*b+t)
    t-=2*b
    n+=2
print(c)