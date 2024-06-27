l, r, n = -1, 1, 0
table = {
    'q1': {'a': ['a', r, 'q2'], 'b': ['b', r, 'q2'], 'c': ['c', r, 'q2'], ' ': [' ', r, 'q1']},
    'q2': {'a': ['a', r, 'q2'], 'b': ['b', r, 'q2'], 'c': ['c', r, 'q2'], ' ': [' ', l, 'q3']},
    'q3': {'a': ['x', r, 'qa'], 'b': ['x', r, 'qb'], 'c': ['x', r, 'qc'], 'x': ['x', l, 'q3'], ' ': [' ', r, 'qe']},
    'q4': {'a': ['a', l, 'q4'], 'b': ['b', l, 'q4'], 'c': ['c', l, 'q4'], 'x': ['x', l, 'q3']},
    'qa': {'a': ['a', r, 'qa'], 'b': ['b', r, 'qa'], 'c': ['c', r, 'qa'], ' ': ['a', l, 'q4'], 'x': ['x', r, 'qa']},
    'qb': {'a': ['a', r, 'qb'], 'b': ['b', r, 'qb'], 'c': ['c', r, 'qb'], ' ': ['b', l, 'q4'], 'x': ['x', r, 'qb']},
    'qc': {'a': ['a', r, 'qc'], 'b': ['b', r, 'qc'], 'c': ['c', r, 'qc'], ' ': ['c', l, 'q4'], 'x': ['x', r, 'qc']},
    'qe': {'a': ['a', n, 'q0'], 'b': ['b', n, 'q0'], 'c': ['c', n, 'q0'], 'x': [' ', r, 'qe']}
}
lent = list(input())
buf = [' ' for i in range(13)]
lent = lent + buf
i = 0
q = 'q1'
while q != 'q0':
    s, mov, state = table[q][lent[i]]
    lent[i] = s
    i += mov
    q = state
print(''.join(lent))
