L, R, N = -1, 1, 0

table = {
    'q1': {'a': ['a', R, 'q2'], 'b': ['b', R, 'q2'], 'c': ['c', R, 'q2'], ' ': [' ', R, 'q1']},
    'q2': {'a': ['a', R, 'q2'], 'b': ['b', R, 'q2'], 'c': ['c', R, 'q2'], ' ': [' ', L, 'q3']},
    'q3': {'a': ['a', L, 'q4'], 'b': ['b', L, 'q4'], 'c': ['c', L, 'q4']},
    'q4': {'a': ['x', R, 'q5'], 'b': ['x', R, 'q6'], 'c': ['x', R, 'q7']},
    'q5': {'a': ['a', R, 'q9'], 'b': ['b', R, 'q9'], 'c': ['c', R, 'q9'], 'x': ['x', R, 'q5']},
    'q6': {'a': ['a', R, 'q10'], 'b': ['b', R, 'q10'], 'c': ['c', R, 'q10'], 'x': ['x', R, 'q6']},
    'q7': {'a': ['a', R, 'q11'], 'b': ['b', R, 'q11'], 'c': ['c', R, 'q11'], 'x': ['x', R, 'q7']},
    'q8': {'a': ['a', L, 'q8'], 'b': ['b', L, 'q8'], 'c': ['c', L, 'q8'], 'x': ['x', L, 'q12']},
    'q9': {'a': ['a', R, 'q9'], 'b': ['b', R, 'q9'], 'c': ['c', R, 'q9'], ' ': ['a', L, 'q8']},
    'q10': {'a': ['a', R, 'q10'], 'b': ['b', R, 'q10'], 'c': ['c', R, 'q10'], ' ': ['b', L, 'q8']},
    'q11': {'a': ['a', R, 'q11'], 'b': ['b', R, 'q11'], 'c': ['c', R, 'q11'], ' ': ['c', L, 'q8']},
    'q12': {'a': ['x', R, 'q5'], 'b': ['x', R, 'q6'], 'c': ['x', R, 'q7'], 'x': ['x', L, 'q12'], ' ': [' ', R, 'q13']},
    'q13': {'x': [' ', R, 'q13'], 'a': ['a', N, 'qT'], 'b': ['b', N, 'qT'], 'c': ['c', N, 'qT']}
}

memory = list(input())
buf = [' 'for i in range(10)]
memory =buf+memory+buf
state = 'q1'
index = 0
states = [state]
while state != 'qT':
    current_symbol = memory[index]
    future = table[state][current_symbol]
    memory[index] = future[0]
    index += future[1]
    state = future[2]
    states += [state]

print(*memory, sep='')
