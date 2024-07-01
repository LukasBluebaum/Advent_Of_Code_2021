with open('input') as f:
    lines = [int(line.rstrip()) for line in f]
print(sum(lines[i] > lines[i-3] for i in range(3,len(lines))))

