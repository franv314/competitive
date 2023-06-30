# Perdonate queste 30 righe di python, ma in questo caso era la strada migliore.

def D(n):
    return len(str(n))

def predict(K, E, N):
    total, old = 0, 1
    d = 1
    while True:
        l, r = old, 10 * old
        while l < r:
            m = (l + r) // 2
            if (D(K * m ** E) > d): r = m
            else: l = m + 1

        if total + d * (l - old) > N: break
        total += d * (l - old);

        old = l;
        d += 1
    return old - 1 + (N - total + d - 1) // d

with open("input.txt", "r") as file:
    K, E, N = map(int, file.readline().split())

with open("output.txt", "w") as file:
    file.write(f"{predict(K, E, N)}")