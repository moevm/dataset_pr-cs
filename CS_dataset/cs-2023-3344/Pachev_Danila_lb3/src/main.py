L = -1
R = 1
N = 0
table = {
    'q1': {' ': [' ', R, 'q1'], 'a': ['a', R, 'q2'], 'b': ['b', R, 'q2'], 'c': ['c', R, 'q2']},
    'q2': {' ': [' ', L, 'q3'], 'a': ['a', R, 'q2'], 'b': ['b', R, 'q2'], 'c': ['c', R, 'q2']},
    'q3': {'a': ['a', L,'q4'], 'b': ['b', L, 'q3'], 'c': ['c', L, 'q3']},
    'q4': {'a': ['a', L, 'q5'], 'b': ['b', L, 'q3'], 'c': ['c', L, 'q3']},
    'q5': {'a': ['a', R, 'q6'], 'b': ['b', R, 'q7'], 'c': ['c', R, 'q8']},
    'q6': {' ': ['a', N, 'qn'], 'a': ['a', R, 'q6'], 'b': ['a', N, 'qn'], 'c': ['a', N, 'qn']},
    'q7': {' ': ['b', N, 'qn'], 'a': ['a', R, 'q7'], 'b': ['b', N, 'qn'], 'c': ['b', N, 'qn']},
    'q8': {' ': ['c', N, 'qn'], 'a': ['a', R, 'q8'], 'b': ['c', N, 'qn'], 'c': ['c', N, 'qn']}

}
tape = list(input())
state = 'q1'
head = 0
direction = 0
while state!='qn':
    tape[head], direction, state = table[state][tape[head]]
    head+=direction
print(''.join(tape))