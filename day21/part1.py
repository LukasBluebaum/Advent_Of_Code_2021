import sys
dice = 0
def roll():
    global dice
    temp = (dice + 1) % 101
    dice = (temp if temp > 0 else 1)
    return dice

pos1 = 10
pos2 = 6

score1 = 0
score2 = 0
rolls = 0
step= 0

while score1 < 1000 and score2 < 1000:
    temp = roll() + roll() + roll()
    if step % 2 == 0:
        x = (pos1 + temp) % 10
        pos1 = x if x > 0 else 10
        score1 += pos1
    else:
        x = (pos2 + temp) % 10
        pos2 = x if x > 0 else 10
        score2 += pos2
    rolls += 3
    step += 1

print(rolls)
print(score1)
print(score2)
print(min(score1, score2) * rolls)
