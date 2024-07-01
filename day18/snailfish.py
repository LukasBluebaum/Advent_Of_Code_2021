import json
import sys
import math
from collections import deque
from itertools import combinations
from copy import copy, deepcopy


def split(l, found = False):
    for idx, c in enumerate(l):
        if isinstance(c, list):
            found = split(c, found)
        else:
            if c >= 10 and not found:
                l[idx] = [math.floor(c/2), math.ceil(c/2)]
                found = True
                return found
    return found

def remove_left(current, idx, x):
    if isinstance(current[idx], list):
        remove_left(current[idx], -1, x)
    else:
        current[idx] += x

def remove_right(current, idx, x):
    if isinstance(current[idx], list):
        remove_right(current[idx], 0, x)
    else:
        current[idx] += x

def remove(stack, to_remove, current_idx):
    current, idx = stack.pop()
    current[current_idx] = 0
    left = False
    right = False
    while(True):
        if not left and current_idx > 0:
            remove_left(current, current_idx-1, to_remove[0])
            left = True
        if not right and current_idx < len(current) - 1:
            remove_right(current, current_idx+1, to_remove[1])
            right = True

        if len(stack) == 0: break
        current_idx = idx
        current, idx = stack.pop()


def explode(l, stack, depth = 0, found = False):
    for idx, c in enumerate(l):
        if isinstance(c, list) and not found:
            if depth == 3:
                remove(copy(stack), c, idx)
                return True
            else:
                stack.append((c, idx))
                found = explode(c, stack, depth+1, found)
                stack.pop()
    return found

def calc_magnitude(l):
    if isinstance(l, int):
        return l
    else:
        return calc_magnitude(l[0]) * 3 + calc_magnitude(l[1])  * 2

def calc_sum(current):
    done = True
    while(done):
        stack = deque()
        stack.append((current,0))
        if not explode(current, stack):
            done = split(current)
    return calc_magnitude(current)



lines = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        lines.append(json.loads(line.rstrip()))

max_ = 0
for l1, l2 in list(combinations(lines, 2)):
    current = deepcopy([l1, l2])
    current2 = deepcopy([l2, l1])
    sum_ = calc_sum(current)
    if sum_ > max_:
        max_ = sum_

    sum_ = calc_sum(current2)
    if sum_ > max_:
        max_ = sum_

print(max_)
