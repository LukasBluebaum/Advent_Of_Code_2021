import sys
from collections import defaultdict, deque

def dfs(graph, node, visited):
    if node == 'end':
        return 1
    count = 0
    if node.islower():
        visited.add(node)
    for n in graph[node]:
        if n not in visited or n == 'end':
            count += dfs(graph, n, visited)
    return count

def check(small, path, node):
    return path.count(node) == 0 or all(path.count(s) <= 1 for s in small)

graph = defaultdict(list)
with open(sys.argv[1], 'r') as file:
    for line in file:
        a, b = line.strip().split('-')
        graph[a].append(b)
        graph[b].append(a)

print(graph)

small = {node for node in graph if node.islower() and node != 'start' and node != 'end'}

print(small)

q = deque()
q.append(['start'])
paths = 0
while q:
    path = q.popleft()
    if path[-1] == 'end':
        paths += 1
        continue
    for node in graph[path[-1]]:
        if node != 'start' and (node == 'end' or node.isupper() or
                                node.islower() and check(small, path, node)):
            q.append(path + [node])

print(paths)


