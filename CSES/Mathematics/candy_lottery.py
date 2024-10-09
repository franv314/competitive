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
    
    def __sub__(self, other):
        return Fraction(self.num * other.den - self.den * other.num, self.den * other.den).reduce()

    def __mul__(self, other):
        return Fraction(self.num * other.num, self.den * other.den).reduce()

    def __pow__(self, exp):
        if exp < 0:
            return Fraction(1, 1) / (self ** -exp)
        if exp == 0:
            return Fraction(1, 1)
        
        h = self ** (exp // 2)
        if exp % 2:
            return h * h * self
        return h * h

    def cmp(self, other):
        return sign(self.num * other.den - self.den * other.num)

n, k = map(int, input().split())
ev = Fraction(0, 1)

for ma in range(1, k + 1):
    p = Fraction(ma, k) ** n - Fraction(ma - 1, k) ** n
    ev = ev + Fraction(ma, 1) * p

v = (ev * Fraction(10 ** 6, 1)).val_int()
h = Fraction(10 * v + 5, 10 ** 7)

c = ev.cmp(h)
if c > 0 or (c == 0 and v % 2 == 1): v += 1

print(f"{v / (10 ** 6):.6f}")
