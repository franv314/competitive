def tris(c, grid):
    return ( grid[0] == grid[1] == grid[2] == c or
             grid[3] == grid[4] == grid[5] == c or
             grid[6] == grid[7] == grid[8] == c or
             grid[0] == grid[3] == grid[6] == c or
             grid[1] == grid[4] == grid[7] == c or
             grid[2] == grid[5] == grid[8] == c or
             grid[0] == grid[4] == grid[8] == c or
             grid[2] == grid[4] == grid[6] == c  )

def win(turn, grid):
    if tris("X", grid):
        return True
    if tris("O", grid) or turn == 9:
        return False
    
    c = "XO"[turn & 1]
    for i in range(9):
        if grid[i] != '.':
            continue
            
        new_grid = "".join(map(lambda j: grid[j] if j != i else c, range(9)))
        res = win(turn + 1, new_grid)
        if (turn & 1) and not res:
            return False
        if not (turn & 1) and res:
            return True
        
    if turn & 1:
        return True
    else:
        return False

def main():
    with open("input.txt", "r") as infile:
        grid = infile.read().replace("\n", "")
    
    turn = 9 - grid.count(".")
    with open("output.txt", "w") as outfile:
        outfile.write("01"[win(turn, grid)])

if __name__ == "__main__":
    main()