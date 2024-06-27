R, L, N = 1, -1, 0
table = { 
    'q0': {'a': ['a', R, 'q2'], 'b':['b', R, 'q1'], 'c':['c', R, 'q1'], ' ':[' ', R, 'q0']},
    'q1': {'a': ['a', R, 'q2'], 'b': ['b', R, 'q1'], 'c': ['c', R, 'q1'], ' ': [' ', N, 'qE']},
    'q2': {'a': ['a', L, 'q3'], 'b': ['b', L, 'q4'], 'c': ['c', L, 'q5'], ' ': [' ', L, 'q3']},
    'q3': {'a': ['a', L, 'q3'], 'b': ['b', L, 'q3'], 'c': ['c', L, 'q3'], ' ': [' ', R, 'q6']},
    'q4': {'a': ['a', L, 'q4'], 'b': ['b', L, 'q4'], 'c': ['c', L, 'q4'], ' ': [' ', R, 'q7']},
    'q5': {'a': ['a', L, 'q5'], 'b': ['b', L, 'q5'], 'c': ['c', L, 'q5'], ' ': [' ', R, 'q8']},
    'q6': {'a': ['a', R, 'q6'], 'b': ['b', R, 'q6'], 'c': ['c', L, 'q9'], ' ': [' ', N, 'qE']},
    'q7': {'a': ['a', R, 'q7'], 'b': ['b', R, 'q7'], 'c': ['c', L, 'q10'], ' ': [' ', N, 'qE']},
    'q8': {'a': ['a', R, 'q8'], 'b': ['b', R, 'q8'], 'c': ['c', L, 'q11'], ' ': [' ', N, 'qE']},
    'q9': {'a': ['a', N, 'qE'], 'b': ['a', N, 'qE'], 'c': ['a', N, 'qE'], ' ': ['a', N, 'qE']},
    'q10': {'a': ['b', N, 'qE'], 'b': ['b', N, 'qE'], 'c': ['b', N, 'qE'], ' ': ['b', N, 'qE']},
    'q11': {'a': ['c', N, 'qE'], 'b': ['c', N, 'qE'], 'c': ['c', N, 'qE'], ' ': ['c', N, 'qE']},
}
memory = list(input())
q = 'q0'
position = 0

while q != 'qE':
    symbol, step, state = table[q][memory[position]]
    memory[position] = symbol
    position += step
    q = state
print(*memory, sep='')
