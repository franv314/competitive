def solve(N):
    if (N == 1):
        print(1)
        return
    if (N == 3):
        print(169)
        print(196)
        print(961)
        return
    else:
        N = (N + 1) // 2
        for i in range(N - 1):
            print(((10 ** (N - 1) + 3 * 10 ** i)) ** 2)
            print(((3 * 10 ** (N - 1) + 10 ** i)) ** 2)
        print((14 * 10 ** (N - 2)) ** 2)

T = int(input())
for _ in range(T):
    N = int(input())
    solve(N)