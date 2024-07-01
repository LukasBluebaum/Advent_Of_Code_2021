import sys
import itertools
from functools import reduce

cubes_temp = []
commands = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        line = line.strip()
        if line.startswith('on'):
            commands.append(True)
        else:
            commands.append(False)
        temp = []
        for a in line.split(','):
            s, e = a.split('..')
            temp.append((s[s.find('=')+1:], e))
        cubes_temp.append(tuple(temp))

cubes = []
for idx, cube in enumerate(cubes_temp):
    temp = []
    temp2 = []
    for i in range(3):
        temp.append(int(cube[i][0]))
        temp2.append(int(cube[i][1]))
    cubes.append((tuple(temp), tuple(temp2), commands[idx]))


def size(cube):
    size = reduce(lambda a, b: a*b, [(y-x)+1 for x,y in zip(cube[0], cube[1])])
    return size if cube[2] else -size

def overlap(cube1, cube2):
    return not (cube2[0][0] > cube1[1][0] or cube2[0][1] > cube1[1][1] or cube2[0][2] > cube1[1][2] \
        or cube2[1][0] < cube1[0][0] or cube2[1][1] < cube1[0][1] or cube2[1][2] < cube1[0][2])

def get_overlap_cube(cube1, cube2):
    start = (max(cube1[0][0], cube2[0][0]), max(cube1[0][1], cube2[0][1]), max(cube1[0][2], cube2[0][2]))
    end = (min(cube1[1][0], cube2[1][0]), min(cube1[1][1], cube2[1][1]), min(cube1[1][2], cube2[1][2]))
    return start, end, not cube2[2]

found_cubes = []
for cube in cubes:
    to_add = []
    for comp_cube in found_cubes:
        if overlap(comp_cube, cube):
            to_add.append(get_overlap_cube(cube, comp_cube))
    if cube[2]:
        to_add.append(cube)
    found_cubes.extend(to_add)

for c in found_cubes:
    print(c)

print(sum(size(cube) for cube in found_cubes))

