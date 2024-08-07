s = list(input())
R = 1
L = -1
N = 0
table = {
    "q1": {'a': ['a', R, 'q2'], 'b': ['b', R, 'q5'], 'c': ['c', R, 'q2'], ' ': [' ', R, 'q1']},
    "q2": {'a': ['a', R, 'q2'], 'b': ['b', R, 'q5'], 'c': ['c', R, 'q2'], ' ': [' ', L, 'q3']},
    "q3": {'a': ['a', L, 'q3'], 'c': ['c', L, 'q3'], ' ': [' ', R, 'q4']},
    "q4": {'a': [' ', N, 'q0'], 'c': [' ', N, 'q0']},
    "q5": {'a': [' ', R, 'q6'], 'b': [' ', R, 'q6'], 'c': [' ', R, 'q6'], ' ': [' ', L, 'q7']},
    "q6": {'a': [' ', R, 'q8'], 'b': [' ', R, 'q8'], 'c': [' ', R, 'q8'], ' ': [' ', R, 'q8']},
    "q7": {'b': [' ', N, 'q0']},
    "q8": {'a': [' ', L, 'q9'], 'b': [' ', L, 'q13'], 'c': [' ', L, 'q15'], ' ': [' ', N, 'q0']},
    "q9": {' ': [' ', L, 'q10']},
    "q10": {' ': ['a', R, 'q11']},
    "q11": {' ': [' ', R, 'q12']},
    "q12": {' ': [' ', R, 'q8']},
    "q13": {' ': [' ', L, 'q14']},
    "q14": {' ': ['b', R, 'q11']},
    "q15": {' ': [' ', L, 'q16']},
    "q16": {' ': ['c', R, 'q11']}
    }
state = "q1"
i = 0
while state != 'q0':
    changes = table[state][s[i]]
    s[i] = changes[0]
    i += changes[1]
    state = changes[2]
print(*s, sep='')
