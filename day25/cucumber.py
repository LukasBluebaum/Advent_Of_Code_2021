import sys
from copy import deepcopy

grid = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        grid.append(list(line.strip()))


for g in grid:
    print(g)

changed = True
runs = 0
while changed:
    changed = False
    temp = deepcopy(grid)
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == '>' and grid[i][(j + 1) % len(grid[0])] == '.':
                grid[i][j] = '.'
                grid[i][(j + 1) % len(grid[0])] = '>'
                changed = True
                j += 1
    grid = temp
    temp = deepcopy(grid)
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == 'v' and grid[(i+1) % len(grid)][j] == '.':
                temp[i][j] = '.'
                temp[(i+1) % len(grid)][j] = 'v'
                changed = True
    runs += 1
    grid = temp

print(runs)
