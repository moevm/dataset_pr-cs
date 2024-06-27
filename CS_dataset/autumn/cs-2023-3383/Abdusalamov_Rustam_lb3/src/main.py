LEFT, RIGHT, NONE = -1, 1, 0

state_table = {
    'q1': {'a': ['a', RIGHT, 'q2'], 'b': ['b', RIGHT, 'q3'], 'c': ['c', RIGHT, 'q2'], ' ': [' ', RIGHT, 'q1']},
    'q2': {'a': ['a', RIGHT, 'q2'], 'b': ['b', RIGHT, 'q3'], 'c': ['c', RIGHT, 'q2'], ' ': [' ', LEFT, 'q4']},
    'q3': {'a': ['', RIGHT, 'q5'], 'b': ['', RIGHT, 'q5'], 'c': ['', RIGHT, 'q5'], ' ': [' ', LEFT, 'q5']},
    'q4': {'a': ['a', LEFT, 'q4'], 'c': ['c', LEFT, 'q4'], ' ': [' ', RIGHT, 'q5']},
    'q5': {'a': ['', NONE, 'q0'], 'b': ['', NONE, 'q0'], 'c': ['', NONE, 'q0'], ' ': [' ', NONE, 'q0']},
}

tape = list(input())
cur_state = 'q1'
index = 0

while cur_state != 'q0':
    move = state_table[cur_state][tape[index]]
    tape[index] = move[0]
    index += move[1]
    cur_state = move[2]

print(''.join(tape))
