T = int(input())
for _ in range(T):
    l, r = map(int, input().split())
    print(r - l if not l == r == 1 else 1)