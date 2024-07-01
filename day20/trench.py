import sys

def convolve(matrix, out, algorithm, flag):
    for x in range(len(matrix)):
        for y in range(len(matrix)):
            if x < 1 or y < 1 or x == len(matrix) - 1 or y == len(matrix)-1:
                if flag:
                    out[x][y] = '1'
                else:
                    out[x][y] = '0'
            else:
                bin_ = matrix[x-1][y-1] + matrix[x-1][y] + matrix[x-1][y+1] + matrix[x][y-1] + matrix[x][y] \
                        + matrix[x][y+1] + matrix[x+1][y-1] + matrix[x+1][y] + matrix[x+1][y+1]
                out[x][y] = '1' if algorithm[int(bin_ ,2)] == '#' else '0'

def get_count(matrix):
    return sum(1 for x in range(len(matrix)) for y in range(len(matrix)) if matrix[x][y] == '1')

def get_matrix(dim):
    matrix = []
    for x in range(dim):
        matrix.append(['0' for _ in range(dim)])
    return matrix


algorithm = None
matrix = []
with open(sys.argv[1], 'r') as file:
    algorithm = file.readline().strip()
    file.readline()
    for line in file:
        line_char = [a for a in line.strip()]
        x = []
        for a in line_char:
            if a == '#':
                x.append('1')
            else:
                x.append('0')
        matrix.append(x)

dim = len(matrix)
x1 = ['0' for x in range(dim)]
x2 = ['0' for x in range(dim)]
x3 = ['0' for x in range(dim)]
x4 = ['0' for x in range(dim)]
matrix.insert(0, x1)
matrix.insert(0, x2)
matrix.append(x3)
matrix.append(x4)
for x in matrix:
    x.insert(0, '0')
    x.insert(0, '0')
    x.append('0')
    x.append('0')


flag = True
for i in range(50):
    #for u in matrix:
    #    print(u)
    #print("\n\n")
    out = get_matrix(dim+4+i*2)
    convolve(matrix, out, algorithm, flag)
    print(get_count(out))
    matrix = out
    symbol = '1' if flag else '0'
    x1 = [symbol for x in range(dim+4+i*2)]
    x2 = [symbol for x in range(dim+4+i*2)]
    matrix.insert(0, x1)
    matrix.append(x2)
    for x in matrix:
        x.insert(0, symbol)
        x.append(symbol)
    flag = not flag

#print(out)
for x in out:
    #print(x)
    pass

