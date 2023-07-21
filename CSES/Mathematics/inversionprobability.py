import math

def sign(x):
    if x > 0: return 1
    if x < 0: return -1
    return 0

class Fraction:
    def __init__(self, num, den):
        self.num = num
        self.den = den

    def val(self):
        return self.num / self.den

    def val_int(self):
        return self.num // self.den

    def __repr__(self):
        return f"{self.num}/{self.den}"

    def reduce(self):
        g = math.gcd(self.num, self.den)
        return Fraction(self.num // g, self.den // g)

    def __add__(self, other):
        return Fraction(self.num * other.den + self.den * other.num, self.den * other.den).reduce()
    
    def __mul__(self, other):
        return Fraction(self.num * other.num, self.den * other.den).reduce()

    def cmp(self, other):
        return sign(self.num * other.den - self.den * other.num)

N = int(input())
R = list(map(int, input().split(" ")))

ans = Fraction(0, 1)

for i in range(N):
    for j in range(i + 1, N):
        cnt = 0
        for x in range(1, R[i] + 1):
            for y in range(1, R[j] + 1):
                cnt += (x > y)
        ans = ans + Fraction(cnt, R[i] * R[j])

v = (ans * Fraction(10 ** 6, 1)).val_int()
h = Fraction(10 * v + 5, 10 ** 7)

c = ans.cmp(h)
if c > 0 or (c == 0 and v % 2 == 1): v += 1

print(f"{v / (10 ** 6):.6f}")