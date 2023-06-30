N, P = map(int, input().split())
S = []
for i in range(N):
    S.append(sum(map(int, input().split())))

S.sort()
print(max(0, (S[-2] + P * 100) - S[-1] + 1))