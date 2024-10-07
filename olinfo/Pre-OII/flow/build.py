#!/bin/python3

import sys
import matplotlib.pyplot as plt

def read(file):
    with open(file, "r") as f:
        N, M, K = map(int, f.readline().split())

        grid = []
        for _ in range(N):
            grid.append(list(map(int, f.readline().split())))

        points = [[] for _ in range(K + 1)]
        for i in range(N):
            for j in range(M):
                points[grid[i][j]].append([i, j])

        points = points[1:]

    return N, M, K, grid, points

def draw(N, M, K, grid):
    plt.close()
    plt.xlim((0, N - 1))
    plt.ylim((0, M - 1))

    for c in range(1, K + 1):
        X, Y = [], []
        for i in range(N):
            for j in range(M):
                if grid[i][j] == c:
                    X.append(i)
                    Y.append(j)
                    plt.text(i, j, str(c - 1))
        plt.scatter(X, Y)
    plt.show()

def main():
    N, M, K, grid, points = read(sys.argv[1])

    while True:
        try:
            match input().split():
                case ["lh", col]:
                    col = int(col)
                    print(points[col])
                case ["ex", col, j, dir, len]:
                    col = int(col)
                    j = int(j)
                    len = int(len)
                    x, y = points[col][j]
                    match dir:
                        case 'N':
                            for i in range(1, len + 1):
                                if grid[x][y + i]:
                                    raise
                            for i in range(1, len + 1):
                                grid[x][y + i] = col + 1
                            points[col][j][1] += len
                        case 'E':
                            for i in range(1, len + 1):
                                if grid[x + i][y]:
                                    raise
                            for i in range(1, len + 1):
                                grid[x + i][y] = col + 1
                            points[col][j][0] += len
                        case 'S':
                            for i in range(1, len + 1):
                                if grid[x][y - i]:
                                    raise
                            for i in range(1, len + 1):
                                grid[x][y - i] = col + 1
                            points[col][j][1] -= len
                        case 'W':
                            for i in range(1, len + 1):
                                if grid[x - i][y]:
                                    raise
                            for i in range(1, len + 1):
                                grid[x - i][y] = col + 1
                            points[col][j][0] -= len
                        case _:
                            raise
                case ["sh"]:
                    draw(N, M, K, grid)
                case _:
                    raise
        except Exception:
            print("?")

if __name__ == "__main__":
    plt.switch_backend("Gtk3Agg")
    main()
