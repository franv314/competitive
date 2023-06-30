from math import *

T = int(input())
for _ in range(T):
    N = int(input())
    g_ab = 0
    l_b = 1
    tags = 1
    for i in range(N):
        a, b = map(int, input().split())
        if i == 0: g_ab = a * b
        else: g_ab = gcd(g_ab, a * b)
        l_b = lcm(l_b, b)

        if g_ab % l_b == 0: continue
        tags += 1
        g_ab = a * b
        l_b = b
    print(tags)