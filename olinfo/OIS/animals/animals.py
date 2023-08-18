N = int(input())
S = list(map(int, input().split()))

curr = []
for s in S:
    curr.append(s)
    curr = [i for i in curr if i >= s]
print(len(curr))