known = {
    1: [
        [0]
    ],
    2: [
        [0, 0],
        [0, 0],
    ],
    3: [
        [1, 1, 1],
        [0, 1, 0],
        [0, 0, 0],
    ],
    4: [
        [1, 1, 1, 2],
        [3, 1, 2, 2],
        [3, 3, 4, 2],
        [3, 4, 4, 4],
    ],
    5: [
        [1, 1, 1, 2, 2],
        [3, 1, 2, 2, 4],
        [3, 3, 0, 4, 4],
        [3, 6, 5, 5, 4],
        [6, 6, 6, 5, 5],
    ],
    6: [
        [1, 1, 1, 2, 2, 3],
        [8, 1, 2, 2, 3, 3],
        [8, 8, 0, 0, 4, 3],
        [7, 8, 0, 0, 4, 4],
        [7, 7, 6, 6, 5, 4],
        [7, 6, 6, 5, 5, 5],
    ],
    7: [
        [ 1,  1,  1,  2,  2,  2,  3],
        [ 4,  1,  5,  5,  2,  3,  3],
        [ 4,  4,  6,  5,  5,  0,  3],
        [ 4,  7,  6,  6,  8,  8,  9],
        [ 7,  7,  6,  8,  8,  9,  9],
        [ 7, 10, 10, 11, 11, 12,  9],
        [10, 10, 11, 11, 12, 12, 12],
    ],
    10: [
        [ 1,  1,  1, 15, 16,  2,  2,  2,  3,  3], 
        [12,  1, 15, 15, 16, 16,  2,  3,  3, 23], 
        [12, 12, 15,  4,  4, 16, 18, 22, 23, 23], 
        [13, 12,  4,  4, 17, 18, 18, 22, 22, 23], 
        [13, 13,  5,  5, 17, 17, 18, 20, 22, 24], 
        [13,  6,  6,  5,  5, 17, 20, 20, 24, 24], 
        [ 6,  6,  7,  7,  8,  8, 19, 20, 25, 24], 
        [14,  7,  7,  8,  8, 19, 19, 21, 25, 25], 
        [14, 14,  9, 10, 10, 19, 21, 21, 11, 25], 
        [14,  9,  9,  9, 10, 10, 21, 11, 11, 11], 
    ]
}

if __name__ == "__main__":
    n = int(input())
    grid = [[0] * n for _ in range(n)]

    curr_block = -1
    curr_row, curr_col = 0, 0

    while n - curr_row >= 8 and n - curr_row != 10:
        grid[curr_row][0] = curr_block
        grid[curr_row + 1][0] = curr_block
        grid[curr_row + 2][0] = curr_block
        grid[curr_row + 1][1] = curr_block

        grid[curr_row][1] = curr_block - 1
        grid[curr_row][2] = curr_block - 1
        grid[curr_row][3] = curr_block - 1
        grid[curr_row + 1][2] = curr_block - 1

        grid[curr_row + 3][0] = curr_block - 2
        grid[curr_row + 3][1] = curr_block - 2
        grid[curr_row + 3][2] = curr_block - 2
        grid[curr_row + 2][1] = curr_block - 2

        curr_block -= 3

        for i in range(3, n - 1):
            r1, r2 = (curr_row + 3, curr_row + 2) if i % 2 else (curr_row, curr_row + 1)
            grid[r1][i] = curr_block
            grid[r1][i + 1] = curr_block
            grid[r2][i - 1] = curr_block
            grid[r2][i] = curr_block
        
            curr_block -= 1

        r1, r2, r3 = (curr_row, curr_row + 1, curr_row + 2) if n % 2 else (curr_row + 1, curr_row + 2, curr_row + 3)
        grid[r1][-1] = curr_block
        grid[r2][-1] = curr_block
        grid[r2][-2] = curr_block
        grid[r3][-1] = curr_block

        curr_block -= 1

        curr_row += 4

    rem = n - curr_row

    while n - curr_col >= 8 and n - curr_col != 10:
        grid[curr_row][curr_col] = curr_block
        grid[curr_row][curr_col + 1] = curr_block
        grid[curr_row + 1][curr_col + 1] = curr_block
        grid[curr_row][curr_col + 2] = curr_block

        grid[curr_row + 1][curr_col] = curr_block - 1
        grid[curr_row + 2][curr_col] = curr_block - 1
        grid[curr_row + 2][curr_col + 1] = curr_block - 1
        grid[curr_row + 3][curr_col] = curr_block - 1

        grid[curr_row][curr_col + 3] = curr_block - 2
        grid[curr_row + 1][curr_col + 3] = curr_block - 2
        grid[curr_row + 1][curr_col + 2] = curr_block - 2
        grid[curr_row + 2][curr_col + 3] = curr_block - 2

        curr_block -= 3

        for i in range(3 + curr_row, n - 1):
            c1, c2 = (curr_col + 3, curr_col + 2) if i % 2 else (curr_col, curr_col + 1)
            grid[i][c1] = curr_block
            grid[i + 1][c1] = curr_block
            grid[i - 1][c2] = curr_block
            grid[i][c2] = curr_block
        
            curr_block -= 1

        c1, c2, c3 = (curr_col, curr_col + 1, curr_col + 2) if n % 2 else (curr_col + 1, curr_col + 2, curr_col + 3)
        grid[-1][c1] = curr_block
        grid[-1][c2] = curr_block
        grid[-2][c2] = curr_block
        grid[-1][c3] = curr_block

        curr_block -= 1

        curr_col += 4

    for i in range(rem):
        for j in range(rem):
            grid[i + curr_row][j + curr_col] = known[rem][i][j]

    add = max(sum(known[rem], []))

    print(n * n // 4 - (n in (2, 3, 6)))
    for row in grid:
        print(*(add - val if val < 0 else val for val in row))
