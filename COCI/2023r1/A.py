parse = lambda l: l[1:4] + l[5:8] + l[9:12]

sudoku = []
for _ in range(13):
    line = input()
    sudoku.append(line)

sudoku = [parse(sudoku[i]) for i in [1, 2, 3, 5, 6, 7, 9, 10, 11]]

for i in range(9):
    found = [False] * 9
    for j in range(9):
        if sudoku[i][j] != '.' and found[ord(sudoku[i][j]) - 49]:
            print("GRESKA")
            exit(0)
        if sudoku[i][j] != '.': found[ord(sudoku[i][j]) - 49] = True

for i in range(9):
    found = [False] * 9
    for j in range(9):
        if sudoku[j][i] != '.' and found[ord(sudoku[j][i]) - 49]:
            print("GRESKA")
            exit(0)
        if sudoku[j][i] != '.': found[ord(sudoku[j][i]) - 49] = True

for x in range(3):
    for y in range(3):
        found = [False] * 9
        for i in range(3 * x, 3 * x + 3):
            for j in range(3 * y, 3 * y + 3):
                if sudoku[i][j] != '.' and found[ord(sudoku[i][j]) - 49]:
                    print("GRESKA")
                    exit(0)
                if sudoku[i][j] != '.': found[ord(sudoku[i][j]) - 49] = True


print("OK")