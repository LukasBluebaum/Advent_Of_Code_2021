from functools import lru_cache

@lru_cache(maxsize=10000)
def dirac(pos1, pos2, score1, score2, step):
    if score1 >= 21:
        return 1, 0
    if score2 >= 21:
        return 0, 1
    one = 0
    two = 0
    if step % 2 == 0:
        for a, b in [(3,1), (9,1), (8,3), (4,3), (7,6), (5,6), (6,7)]:
            x = (pos1 + a) % 10
            new_pos = x if x > 0 else 10
            run = dirac(new_pos, pos2, score1+new_pos, score2, step+1)
            one += run[0] * b
            two += run[1] * b
    else:
        for a, b in [(3,1), (9,1), (8,3), (4,3), (7,6), (5,6), (6,7)]:
            x = (pos2 + a) % 10
            new_pos = x if x > 0 else 10
            run = dirac(pos1, new_pos, score1, score2+new_pos, step+1)
            one += run[0] * b
            two += run[1] * b

    return one, two

pos1 = 10
pos2 = 6
print(dirac(pos1, pos2, 0, 0, 0))
