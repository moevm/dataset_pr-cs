program={'q0': {'a': ('a', 0, 'qp'), ' ': (' ', 1, 'q0')},
         'qp': {'a': ('p', -1, 'qa'), 'b': ('p', -1, 'qb'), 'c': ('p', -1, 'qc'), 'p': ('p', 1, 'qp'), ' ': (' ', -1, 'q2')},
         'qa': {'a': ('a', -1, 'qa'), 'b': ('b', -1, 'qa'), 'c': ('c', -1, 'qa'), 'p': ('p', -1, 'qa'), ' ': ('a', 1, 'q1')},
         'qb': {'a': ('a', -1, 'qb'), 'b': ('b', -1, 'qb'), 'c': ('c', -1, 'qb'), 'p': ('p', -1, 'qb'), ' ': ('b', 1, 'q1')},
         'qc': {'a': ('a', -1, 'qc'), 'b': ('b', -1, 'qc'), 'c': ('c', -1, 'qc'), 'p': ('p', -1, 'qc'), ' ': ('c', 1, 'q1')},
         'q1': {'a': ('a', 1, 'q1'), 'b': ('b', 1, 'q1'), 'c': ('c', 1, 'q1'), 'p': ('p', 1, 'qp')},
         'q2': {'a': ('a', 0, 'q3'), 'p': (' ', -1, 'q2')}
         }
tape=list(' '*15+input()+' '*15)
state='q0'
index=0
while state!='q3':
    symbol,move_to,state_new=program[state][tape[index]]
    tape[index]=symbol
    index+=move_to
    state=state_new
print(''.join(tape))