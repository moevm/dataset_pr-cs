L, N, R = -1, 0, 1
table = {
    'q0': {'a': ['a', R, 'q2'], 'b': ['b', R, 'q1'], 'c': ['c', R, 'q1'], ' ': [' ', R, 'q0']},
    'q1': {'a': ['a', R, 'q2'], 'b': ['b', R, 'q1'], 'c': ['c', R, 'q1'], ' ': [' ', N, 'q12']},
    'q2': {'a': ['a', L, 'q3'], 'b': ['b', L, 'q4'], 'c': ['c', L, 'q5'], ' ': [' ', L, 'q3']},
    'q3': {'a': ['a', L, 'q3'], 'b': ['b', L, 'q3'], 'c': ['c', L, 'q3'], ' ': [' ', R, 'q6']},
    'q4': {'a': ['a', L, 'q4'], 'b': ['b', L, 'q4'], 'c': ['c', L, 'q4'], ' ': [' ', R, 'q7']},
    'q5': {'a': ['a', L, 'q5'], 'b': ['b', L, 'q5'], 'c': ['c', L, 'q5'], ' ': [' ', R, 'q8']},
    'q6': {'a': ['a', R, 'q6'], 'b': ['b', R, 'q6'], 'c': ['c', L, 'q9'], ' ': [' ', N, 'q12']},
    'q7': {'a': ['a', R, 'q7'], 'b': ['b', R, 'q7'], 'c': ['c', L, 'q10'], ' ': [' ', N, 'q12']},
    'q8': {'a': ['a', R, 'q8'], 'b': ['b', R, 'q8'], 'c': ['c', L, 'q11'], ' ': [' ', N, 'q12']},
    'q9': {'a': ['a', N, 'q12'], 'b': ['a', N, 'q12'], 'c': ['a', N, 'q12'], ' ': ['a', N, 'q12']},
    'q10': {'a': ['b', N, 'q12'], 'b': ['b', N, 'q12'], 'c': ['b', N, 'q12'], ' ': ['b', N, 'q12']},
    'q11': {'a': ['c', N, 'q12'], 'b': ['c', N, 'q12'], 'c': ['c', N, 'q12'], ' ': ['c', N, 'q12']}
}
line = list(input())
state = 'q0'
position = 0

while state != 'q12':
    line[position], shift, state = table[state][line[position]]
    position += shift

print(''.join(line))
