def __(n): return bool(n)

def solve():
    K = int(input().strip())
    S = input().strip()

    for _ in range(K):
        S = S.replace(chr(ord('a') + _), f"(__(N * {1 << _}))")
    S = S.replace("!", " not ").replace("&", " and ").replace("*", "&")

    total = 0
    for N in range(1 << K):
        total += eval(S)
    print(total)

T = int(input().strip())
for _ in range(T):
    solve()