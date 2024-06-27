Table = {'q0': {'a': ['a', 1, 'q1'], 'b': ['b', 1, 'q1'], 'c': ['c', 1, 'q1'], ' ': [' ', 1, 'q0']},
        'q1': {'a': ['a', 1, 'q1'], 'b': ['b', 1, 'q1'], 'c': ['c', 1, 'q1'], ' ': [' ', -1, 'q2']},
        'q2': {'a': ['a', -1, 'q3'], 'b': ['b', -1, 'q2'], 'c': ['c', -1, 'q2']},
        'q3': {'a': ['a', -1, 'q4'], 'b': ['b', -1, 'q2'], 'c': ['c', -1, 'q2']},
        'q4': {'a': ['a', 1, 'q5'], 'b': ['b', 1, 'q6'], 'c': ['c', 1, 'q7']},
        'q5': {'a': ['a', 1, 'q5'], 'b': ['a', 0, 'q8'], 'c': ['a', 0, 'q8'], ' ': ['a', 0, 'q8']},
        'q6': {'a': ['a', 1, 'q6'], 'b': ['b', 0, 'q8'], 'c': ['b', 0, 'q8'], ' ': ['b', 0, 'q8'] },
        'q7': {'a': ['a', 1, 'q7'], 'b': ['c', 0, 'q8'], 'c': ['c', 0, 'q8'], ' ': ['c', 0, 'q8']}}

mem = list(input())
mem.append(' ')
q = 'q0'
i = 0

while q != 'q8':
    s, mv, st = Table[q][mem[i]]
    mem[i] = s
    i += mv
    q = st

print("".join(mem))
