def check(a, b):
    return (a, b) in [(1, "R"), (2, "Y"), (3, "C")]

h = []
c = []

r = ""
while True:
    r = input()
    if r in "123": h.append(int(r))
    else: break

while True:
    c.append(r)
    try: r = input()
    except: break

for i in range(len(h)):
    if not check(h[i], c[i]):
        print("NO")
        exit(0)
print("YES")