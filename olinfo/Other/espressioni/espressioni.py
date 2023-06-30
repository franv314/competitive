#Yes, the whole program is inside a try-except, but it works
class Ind(BaseException): pass
class Imp(BaseException): pass

class MyNum:
    def __init__(self, num, den = 1):
        if (num, den) == (0, 0):
            raise Ind
        if den == 0:
            raise Imp
        self.num = num
        self.den = den

    def __repr__(self):
        return repr(self.num / self.den)

    def __add__(self, o):
        return MyNum(self.num * o.den + o.num * self.den, self.den * o.den)

    def __sub__(self, o):
        return MyNum(self.num * o.den - o.num * self.den, self.den * o.den)

    def __pos__(self):
        return MyNum(self.num, self.den)

    def __neg__(self):
        return MyNum(-self.num, self.den)

    def __mul__(self, o):
        return MyNum(self.num * o.num, self.den * o.den)

    def __truediv__(self, o):
        return MyNum(self.num * o.den, self.den * o.num)

def is_num(c):
    return ord('0') <= ord(c) <= ord('9')
try:
    closers = {'{': '}', '[': ']', '(': ')'}
    higher = {'(': '[.({', '[': '{.', '{': '.'}

    with open("input.txt", "r") as file:
        expr = file.read()

    brackets = [['.', 0b111]]
    last_was_op = False
    for c in expr[:-1]:
        if is_num(c):
            brackets[-1][1] |= 0b100
        if c in "+-*/":
            if last_was_op:
                raise
            last_was_op = True
        else:
            last_was_op = False
        if c in "+*/" and brackets[-1][1] & 0b100:
            brackets[-1][1] |= 0b010
        if c == '-':
            brackets[-1][1] |= 0b010
        if c in "([{":
            brackets[-1][1] |= 0b100
            if brackets[-1][0] == higher[c][0]:
                brackets[-1][1] |= 0b001
            if brackets[-1][0] in higher[c]:
                brackets.append([c, int(c == '(')])
            else:
                raise
        if c in ")]}":
            if c == closers[brackets[-1][0]] and brackets[-1][1] == 0b111:
                brackets = brackets[:-1]
            else:
                raise

    expr = "+" + expr[:-1].replace("[", "(").replace("]", ")").replace("{", "(").replace("}", ")") + " "
    new_expr = ""

    for i in range(len(expr) - 1):
        if (expr[i] not in "()[]{}+-*/0123456789"):
            raise
        new_expr += expr[i]
        if not is_num(expr[i]) and is_num(expr[i + 1]):
            new_expr += "MyNum("
        if is_num(expr[i]) and not is_num(expr[i + 1]):
            new_expr += ")"

    with open("output.txt", "w") as file:
        file.write(f"risultato: {eval(new_expr)}")
except Ind:
    with open("output.txt", "w") as file:
        file.write("indeterminata")
except Imp:
    with open("output.txt", "w") as file:
        file.write("impossibile")
except:
    with open("output.txt", "w") as file:
        file.write("errore")