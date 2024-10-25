def cells(n, m):
    if swap := n < m:
        n, m = m, n
    i, j = 0, 0
    
    p = lambda i, j: (j, i) if swap else (i, j)

    while True:
        while j >= m:
            i += 1
            j = i & 1
        if i >= n:
            break

        yield p(i, j)
        j += 2
    
    i, j = 0, 1
    while True:
        while j >= m:
            i += 1
            j = (i & 1) ^ 1
        if i >= n:
            break
        
        yield p(i, j)
        j += 2

if __name__ == "__main__":
    N, M, R, G, B = map(int, input().split())
    
    if max(R, G, B) > (N * M + 1) // 2:
        print("NO")
    else:
        print("YES")
        grid = [[None for _ in range(M)] for _ in range(N)]

        order = sorted("RGB", key = lambda c: globals()[c], reverse = True)
        order[1], order[2] = order[2], order[1]
        order = "".join(globals()[c] * c for c in order)
        for c, (i, j) in zip(order, cells(N, M)):
            grid[i][j] = c

        for row in grid:
            print("".join(row))