R, L, N = 1, -1, 0

table = {
  'q0': {'a': ['a', N, 'q1'], 'b': ['b', N, 'q1'], 'c': ['c', N, 'q1'], ' ': [' ', R, 'q0']},
  'q1': {'a': ['a', R, 'q1'], 'b': ['b', R, 'q1'], 'c': ['c', R, 'q1'], ' ': [' ', L, 'q2']},
  
  'q2': {'a': ['a', L, 'q3'], 'b': ['b', L, 'q2'], 'c': ['c', L, 'q2']},
  'q3': {'a': ['a', L, 'q4'], 'b': ['b', L, 'q2'], 'c': ['c', L, 'q2']},
  'q4': {'a': ['a', R, 'q5'], 'b': ['b', R, 'q7'], 'c': ['c', R, 'q9'], ' ': [' ', R, 'q11']},
  
  'q5': {'a': ['a', R, 'q5'], 'b': ['b', N, 'q6'], 'c': ['c', N, 'q6'], ' ': ['a', N, 'q6']},
  'q6': {'a': ['a', N, 'qF'], 'b': ['a', N, 'qF'], 'c': ['a', N, 'qF'], ' ': ['a', N, 'qF']},

  'q7': {'a': ['a', R, 'q7'], 'b': ['b', N, 'q8'], 'c': ['c', N, 'q8'], ' ': ['a', N, 'q8']},
  'q8': {'a': ['b', N, 'qF'], 'b': ['b', N, 'qF'], 'c': ['b', N, 'qF'], ' ': ['b', N, 'qF']},
  
  'q9': {'a': ['a', R, 'q9'], 'b': ['b', N, 'q10'], 'c': ['c', N, 'q10'], ' ': ['a', N, 'q10']},
  'q10': {'a': ['c', N, 'qF'], 'b': ['c', N, 'qF'], 'c': ['c', N, 'qF'], ' ': ['c', N, 'qF']},

  'q11': {'a': ['a', R, 'q11'], 'b': ['b', N, 'q12'], 'c': ['c', N, 'q12'], ' ': [' ', R, 'q12']},
  'q12': {'a': [' ', N, 'qF'], 'b': [' ', N, 'qF'], 'c': [' ', N, 'qF'], ' ': [' ', N, 'qF']},
}

tape = ' ' + input() + ' '
state = 'q0'
pos = 0

while state!='qF':
  commands = table[state]
  commands = commands[tape[pos]]
  tape = list(tape)
  tape[pos] = commands[0]
  tape = ''.join(tape)
  pos += commands[1]
  state = commands[2]

print(tape)
