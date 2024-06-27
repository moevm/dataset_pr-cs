table = {'q0':  {'a': ['a', 1, 'q1'], 'b': ['b', 1, 'q0'], 'c': ['c', 1, 'q0'], ' ': [' ', 1, 'q0']},
         'q1':  {'a': ['a', -1, 'qa-'], 'b': ['b', -1, 'qb-'], 'c': ['c', -1, 'qc-'], ' ': [' ', -1, 'qa-']},
         'qa-': {'a': ['a', -1, 'qa-'], 'b': ['b', -1, 'qa-'], 'c': ['c', -1, 'qa-'], ' ': [' ', 1, 'qa+']},
         'qa+': {'a': ['a', 1, 'qa+'], 'b': ['b', 1, 'qa+'], 'c': ['c', -1, 'qaw'], ' ': []},
         'qaw': {'a': ['a', 0, 'qend'], 'b': ['a', 0, 'qend'], 'c': ['a', 0, 'qend'], ' ': ['a', 0, 'qend']},
         'qb-': {'a': ['a', -1, 'qb-'], 'b': ['b', -1, 'qb-'], 'c': ['c', -1, 'qb-'], ' ': [' ', 1, 'qb+']},
         'qb+': {'a': ['a', 1, 'qb+'], 'b': ['b', 1, 'qb+'], 'c': ['c', -1, 'qbw'], ' ': []},
         'qbw': {'a': ['b', 0, 'qend'], 'b': ['b', 0, 'qend'], 'c': ['b', 0, 'qend'], ' ': ['b', 0, 'qend']},
         'qc-': {'a': ['a', -1, 'qc-'], 'b': ['b', -1, 'qc-'], 'c': ['c', -1, 'qc-'], ' ': [' ', 1, 'qc+']},
         'qc+': {'a': ['a', 1, 'qc+'], 'b': ['b', 1, 'qc+'], 'c': ['c', -1, 'qcw'], ' ': []},
         'qcw': {'a': ['c', 0, 'qend'], 'b': ['c', 0, 'qend'], 'c': ['c', 0, 'qend'], ' ': ['c', 0, 'qend']},
         }

memory = list(input())
q = 'q0'
index = 0

while q != 'qend' and index < len(memory):
    s, move, state = table[q][memory[index]]
    memory[index] = s
    index += move
    q = state

print(*memory, sep='')
