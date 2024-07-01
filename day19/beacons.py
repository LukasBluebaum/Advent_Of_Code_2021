import sys
from copy import deepcopy
from functools import reduce
from itertools import combinations


rotations =[lambda x, y, z: (x, y, z), lambda x, y, z: (x, -z, y), lambda x, y, z: (x, -y, -z),
            lambda x, y, z: (x, z, -y),
            #-------------------------
            lambda x, y, z: (y, -x, z), lambda x, y, z: (y, z, x), lambda x, y, z: (y, x, -z),
            lambda x, y, z: (y, -z, -x),
            #-------------------------
            lambda x, y, z: (z, x, y), lambda x, y, z: (z, y, -x), lambda x, y, z: (z, -x, -y),
            lambda x, y, z: (z, -y, x),
            #-------------------------
            lambda x, y, z: (-x, -y, z), lambda x, y, z: (-x, z, y), lambda x, y, z: (-x, y, -z),
            lambda x, y, z: (-x, -z, -y),
            #-------------------------
            lambda x, y, z: (-y, x, z), lambda x, y, z: (-y, z, -x), lambda x, y, z: (-y, -x, -z),
            lambda x, y, z: (-y, -z, x),
            #-------------------------
            lambda x, y, z: (-z, y, x), lambda x, y, z: (-z, -x, y), lambda x, y, z: (-z, -y, -x),
            lambda x, y, z: (-z, x, -y)]


def transform(p1, p2):
    return tuple(x - y for x, y in zip(p1, p2))

def manhattan(p1, p2):
    return reduce(lambda x, y: x + y, [abs(x - y) for x, y in zip(p1, p2)])

def combine(beacons, scanner):
    for rotation in rotations:
        rotated = {rotation(*o) for o in scanner}
        for b in beacons:
            for p in rotated:
                pos = transform(p, b)
                temp_beacons = {transform(x, pos) for x in rotated}
                if len(temp_beacons & beacons) >= 12:
                    print("Found match")
                    return temp_beacons, pos
    return None, None


scanners = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        if line.startswith("---"):
            current = set()
        elif len(line) > 1:
            current.add(tuple(map(int, line.rstrip().split(','))))
        else:
            scanners.append(current)


beacons = scanners[0]
del scanners[0]

positions = [(0,0,0)]
while scanners:
    found = -1
    for idx, sc in enumerate(scanners):
        found_beacons, pos = combine(beacons, sc)
        if found_beacons:
            beacons |= found_beacons
            found = idx
            positions.append(pos)
            break
    if found >= 0:
        del scanners[found]

print(len(beacons))
print(positions)
print(max(manhattan(x, y) for x, y in combinations(positions, 2)))










