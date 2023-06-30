N = int(input())
D = int(input())
k = (10 ** (N - 1) + D - 1) // D
A, B = k * D, (k + 1) * D
if B >= 10 ** N: print(0, 0)
else: print(A, B)