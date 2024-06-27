table = {
    'q0': {'a': ['a', 1, 'q1'], 'b': ['b', 1, 'q1'], 'c': ['c', 1, 'q1'], ' ': [' ', 1, 'q0']},
    'q1': {'a': ['a', 1, 'q1'], 'b': ['b', 1, 'q1'], 'c': ['c', 1, 'q1'], ' ': ['N', -1, 'q2']},

    'q2': {'a': ['N', 1, 'q3'], 'b': ['N', 1, 'q4'], 'c': ['N', 1, 'q5'], ' ': [' ', 1, 'qc'], 'N': ['N', -1, 'q2']},
    'qN': {'a': ['a', -1, 'qN'], 'b': ['b', -1, 'qN'], 'c': ['c', -1, 'qN'], 'N': ['N', -1, 'q2']},

    'q3': {'a': ['a', 1, 'q3'], 'b': ['b', 1, 'q3'], 'c': ['c', 1, 'q3'], ' ': ['a', -1, 'qN'], 'N': ['N', 1, 'q3']},
    'q4': {'a': ['a', 1, 'q4'], 'b': ['b', 1, 'q4'], 'c': ['c', 1, 'q4'], ' ': ['b', -1, 'qN'], 'N': ['N', 1, 'q4']},
    'q5': {'a': ['a', 1, 'q5'], 'b': ['b', 1, 'q5'], 'c': ['c', 1, 'q5'], ' ': ['c', -1, 'qN'], 'N': ['N', 1, 'q5']},

    'qc': {'a': ['a', 0, 'qt'], 'b': ['b', 0, 'qt'], 'c': ['c', 0, 'qt'], ' ': [' ', 1, 'qc'], 'N': [' ', 1, 'qc']}

}

line = list(input()+'             ')
q = 'q0'
stt = [q]
mov = 0

while q != 'qt':
    sym, step, st = table[q][line[mov]]

    line[mov] = sym
    mov += step
    q = st

    stt.append(q)

print(''.join(line))