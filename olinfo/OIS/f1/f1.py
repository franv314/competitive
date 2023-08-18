input()
H = list(map(int, input().split()))
V = list(map(int, input().split()))

print("Hamilton" if sum(H) < sum(V) else "Verstappen")
print("Hamilton" if min(H) < min(V) else "Verstappen")