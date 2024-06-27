def move(direction):
    if direction == 'L':
        return -1
    elif direction == 'N':
        return 0 
    else:
        return 1

table = {
    'q1': {'a': ('a', 'L', 'q2'), 'b': ('b', 'L', 'q2'), 'c': ('c', 'L', 'q2'), ' ': (' ', 'R', 'q1')},
    'q2': {' ': ('d', 'R', 'q3')},
    'q3': {'a': ('a', 'R', 'q3'), 'b': ('b', 'R', 'q3'), 'c': ('c', 'R', 'q3'), ' ': (' ', 'L', 'q4')},
    'q4': {'a': ('a', 'L', 'q5'), 'b': ('b', 'L', 'q5'), 'c': ('c', 'L', 'q5')},
    'q5': {'a': (' ', 'R', 'q10'), 'b': (' ', 'R', 'q11'), 'c': (' ', 'R', 'q12'), ' ': (' ', 'L', 'q5'), 'd': (' ', 'N', 'qT')},
    'q6': {'a': ('a', 'R', 'q6'), 'b': ('b', 'R', 'q6'), 'c': ('c', 'R', 'q6'), ' ': ('a', 'L', 'q9')},
    'q7': {'a': ('a', 'R', 'q7'), 'b': ('b', 'R', 'q7'), 'c': ('c', 'R', 'q7'), ' ': ('b', 'L', 'q9')},
    'q8': {'a': ('a', 'R', 'q8'), 'b': ('b', 'R', 'q8'), 'c': ('c', 'R', 'q8'), ' ': ('c', 'L', 'q9')},
    'q9': {'a': ('a', 'L', 'q9'), 'b': ('b', 'L', 'q9'), 'c': ('c', 'L', 'q9'), ' ': (' ', 'L', 'q5')},
    'q10': {'a': ('a', 'N', 'q6'), 'b': ('b', 'N', 'q6'), 'c': ('c', 'N', 'q6'), ' ': (' ', 'R', 'q10')},
    'q11': {'a': ('a', 'N', 'q7'), 'b': ('b', 'N', 'q7'), 'c': ('c', 'N', 'q7'), ' ': (' ', 'R', 'q11')},
    'q12': {'a': ('a', 'N', 'q8'), 'b': ('b', 'N', 'q8'), 'c': ('c', 'N', 'q8'), ' ': (' ', 'R', 'q12')},
}

tape_length = 20
memory = list(input() + " "*tape_length)
q = ['q1']
idx = 0 

while q[-1] != 'qT':
    symbol = memory[idx]
    q_curr = q[-1]
    memory[idx] = table[q_curr][symbol][0]
    idx += move(table[q_curr][symbol][1])
    q.append(table[q_curr][symbol][2])

print(''.join(memory))
