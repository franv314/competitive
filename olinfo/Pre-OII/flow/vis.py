#!/bin/python3

import matplotlib.pyplot as plt
plt.switch_backend("Gtk3Agg")

N, M, K = map(int, input().split())

grid = []
for _ in range(N):
    grid.append(list(map(int, input().split())))

points = [([], []) for _ in range(K + 1)]
for i in range(N):
    for j in range(M):
        points[grid[i][j]][0].append(i)
        points[grid[i][j]][1].append(j)

plt.xlim((0, N - 1))
plt.ylim((0, M - 1))

for i, (x, y) in enumerate(points[1:]):
    plt.scatter(x, y)
    for x0, y0 in zip(x, y):
        plt.text(x0, y0, str(i))

plt.show()
