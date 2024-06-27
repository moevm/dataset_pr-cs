cells = list(input())
state = 'start'
i = 0
R, L, N = 1, -1, 0
table = {'start': {'a': ['a', R, 'q2'], 'b': ['b', R, 'q2'], 'c': ['c', R, 'q2'], ' ': [' ', R, 'start']},
         'q2': {'a': ['a', R, 'q2'], 'b': ['b', R, 'q2'], 'c': ['c', R, 'q2'], ' ': [' ', L, 'q3']},
         'q3': {'a': ['a', L, 'q4'], 'b': ['b', L, 'q3'], 'c': ['c', L, 'q3']},
         'q4': {'a': ['a', L, 'found_aa'], 'b': ['b', L, 'q3'], 'c': ['c', L, 'q3']},
         'found_aa': {'a': ['a', R, 'found_aaa'], 'b': ['b', R, 'found_baa'], 'c': ['c', R, 'found_caa']},
         'found_aaa': {'a': ['a', R, 'found_aaa'], 'b': ['a', N, 'end'], 'c': ['a', N, 'end'], ' ': ['a', N, 'end']},
         'found_baa': {'a': ['a', R, 'found_baa'], 'b': ['b', N, 'end'], 'c': ['b', N, 'end'], ' ': ['b', N, 'end']},
         'found_caa': {'a': ['a', R, 'found_caa'], 'b': ['c', N, 'end'], 'c': ['c', N, 'end'], ' ': ['c', N, 'end']}
         }
while state != 'end':
    cells[i], t, state = table[state][cells[i]]
    i += t
print("".join(cells))
