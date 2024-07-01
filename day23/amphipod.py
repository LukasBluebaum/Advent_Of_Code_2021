from copy import deepcopy
from collections import deque, defaultdict

pod_length = 0

def pod_position(pod):
    return pod * 2

def new_state(pod, positions):
    return deepcopy(pod), deepcopy(positions)

def dest_pod(current):
    if current.startswith('A'): return 1
    if current.startswith('B'): return 2
    if current.startswith('C'): return 3
    if current.startswith('D'): return 4

def cost(current):
    if current.startswith('A'): return 1
    if current.startswith('B'): return 10
    if current.startswith('C'): return 100
    if current.startswith('D'): return 1000

def check_path(current_pos, dest, positions):
    pod_pos = pod_position(dest)
    length = 0
    if pod_pos < current_pos:
        for i in range(current_pos-1,pod_pos-1, -1):
            length+=1
            if positions[i] != '0':
                return False, -1
        return True, length
    else:
        for i in range(current_pos+1,pod_pos+1):
            length+=1
            if positions[i] != '0':
                return False, -1
        return True, length

def check_pod(current, pod):
    return len(pod) == 0 or all(pod[i][0] == current[0] for i in range(len(pod)))

def check_done(pods):
    a = len(pods[1]) == pod_length and all(pods[1][i][0] == 'A' for i in range(pod_length))
    b = len(pods[2]) == pod_length and all(pods[2][i][0] == 'B' for i in range(pod_length))
    c = len(pods[3]) == pod_length and all(pods[3][i][0] == 'C' for i in range(pod_length))
    d = len(pods[4]) == pod_length and all(pods[4][i][0] == 'D' for i in range(pod_length))
    return a and b and c and d

def print_state(pods, positions):
    print(" ".join(positions))
    for p in pods:
        print(pods[p])

def check_partly_solved(index, pod_idx, pod, current):
    return pod_idx == dest_pod(current) and all(i[0] == current[0] for i in pod[index::-1])

def possible_positions(pods, positions, current, current_pos):
    if isinstance(current_pos, tuple):
        pod = current_pos[1]
        index = pods[pod].index(current)
        if index != len(pods[pod]) - 1 or check_partly_solved(index, pod, pods[pod], current):
            yield None, None, None
        else:
            start = pod_position(pod)
            not_allowed = {2, 4, 6, 8}
            for i in range(start+1, len(positions)):
                if positions[i] != '0': break
                if i not in not_allowed:
                    new_pods, new_positions = new_state(pods, positions)
                    del new_pods[pod][index]
                    new_positions[i] = current
                    #--------------------
                    length = i - start
                    length += (pod_length-index)
                    c = cost(current)*length
                    yield new_pods, new_positions, c
            for i in range(start-1, -1, -1):
                if positions[i] != '0': break
                if i not in not_allowed:
                    new_pods, new_positions = new_state(pods, positions)
                    del new_pods[pod][index]
                    new_positions[i] = current
                    #--------------------
                    length = abs(i - start)
                    length += (pod_length-index)
                    c = cost(current)*length
                    yield new_pods, new_positions, c
    else:
        dest = dest_pod(current)
        if len(pods[dest]) == pod_length or not check_pod(current, pods[dest]):
            return None, None, None
        free, length = check_path(current_pos, dest, positions)
        if free:
            new_pods, new_positions = new_state(pods, positions)
            new_positions[current_pos] = '0'
            new_pods[dest].append(current)
            length += (pod_length - len(new_pods[dest])) + 1
            c = cost(current)*length
            yield new_pods, new_positions, c
        else:
            return None, None, None

def hash_config(pods, position):
    dict_key = str(pods)
    list_key = str(position)
    return dict_key, list_key

def find_path(pods_in, positions_in):
    configs = defaultdict(lambda:2**31)
    configs[hash_config(pods_in, positions_in)] = 0
    q = deque()
    q.append((pods_in, positions_in))
    done = set()
    while q:
        pods, positions = q.popleft()
        old_key = hash_config(pods, positions)
        if check_done(pods):
            done.add(configs[old_key])
            continue
        for idx, i in enumerate(positions):
            if i == '0': continue
            for new_pods, new_positions, path_cost in possible_positions(pods, positions, i, idx):
                if new_pods is not None:
                    new_key = hash_config(new_pods, new_positions)
                    if configs[old_key] + path_cost < configs[new_key]:
                        configs[new_key] = configs[old_key] + path_cost
                        q.append((new_pods, new_positions))
        for p in pods:
            if len(pods[p]) == 0: continue
            for new_pods, new_positions, path_cost in possible_positions(pods, positions, pods[p][-1], (-1,p)):
                if new_pods is not None:
                    new_key = hash_config(new_pods, new_positions)
                    if configs[old_key] + path_cost < configs[new_key]:
                        configs[new_key] = configs[old_key] + path_cost
                        q.append((new_pods, new_positions))

    print(min(done))

pods = {}
#pods[1] = ['A1', 'B1']
#pods[2] = ['D1', 'C1']
#pods[3] = ['C2', 'B2']
#pods[4] = ['A2', 'D2']

#pods[1] = ['A1', 'D1', 'D2', 'B1']
#pods[2] = ['D3', 'B2', 'C1', 'C2']
#pods[3] = ['C3', 'A2', 'B3', 'B4']
#pods[4] = ['A3', 'C4', 'A4', 'D4']

#pods[1] = ['B1', 'A1']
#pods[2] = ['C1', 'D1']
#pods[3] = ['A2', 'B2']
#pods[4] = ['C2', 'D2']

pods[1] = ['B1', 'D1', 'D2', 'A1']
pods[2] = ['C1', 'B2', 'C2', 'D3']
pods[3] = ['A2', 'A3', 'B3', 'B4']
pods[4] = ['C3', 'C4', 'A4', 'D4']
pod_length = len(pods[1])
positions = ['0', '0','0', '0','0', '0','0', '0','0', '0','0']

find_path(pods, positions)
