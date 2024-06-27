L, R, N = -1, 1, 0
table = {
    'q1': {'a': ['a', R, 'q2'], 'b': ['b', R, 'q3'], 'c': ['c', R, 'q2'], ' ': [' ', R, 'q1']},
    'q2': {'a': ['a', R, 'q2'], 'b': ['b', R, 'q3'], 'c': ['c', R, 'q2'], ' ': [' ', L, 'q4']},
    'q3': {'a': ['', R, 'q5'], 'b': ['', R, 'q5'], 'c': ['', R, 'q5'], ' ': [' ', L, 'q5']},
    'q4': {'a': ['a', L, 'q4'],  'c': ['c', L, 'q4'], ' ': [' ', R, 'q5']},
    'q5': {'a': ['', N, 'q0'], 'b': ['', N, 'q0'], 'c': ['', N, 'q0'],  ' ': [' ', N, 'q0']},
}

memory = list(input())
state = 'q1'
ind = 0
while state != 'q0':
    act = table[state][memory[ind]]
    memory[ind] = act[0]
    ind += act[1]
    state = act[2]
print(''.join(memory))