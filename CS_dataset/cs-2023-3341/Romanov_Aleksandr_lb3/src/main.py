table = {'q_start': {'a': ('a', 1, 'q_f'),
                     'b': ('b', 1, 'q_f'),
                     'c': ('c', 1, 'q_f'),
                     ' ': (' ', 1, 'q_start')
                     },
         'q_f': {'a': ('a', 1, 'q_f'),
                 'b': ('b', 1, 'q_f'),
                 'c': ('c', 1, 'q_f'),
                 ' ': (' ', -1, 'q_rv')
                 },
         'q_rv': {'a': ('0', 1, 'q_a'),
                  'b': ('0', 1, 'q_b'),
                  'c': ('0', 1, 'q_c'),
                  'A': ('A', -1, 'q_rv'),
                  'B': ('B', -1, 'q_rv'),
                  'C': ('C', -1, 'q_rv'),
                  '0': ('0', -1, 'q_rv'),
                  ' ': (' ', 1, 'q_end'),
                  },
         'q_a': {'a': ('a', 1, 'q_a'),
                 'b': ('b', 1, 'q_a'),
                 'c': ('c', 1, 'q_a'),
                 'A': ('A', 1, 'q_a'),
                 'B': ('B', 1, 'q_a'),
                 'C': ('C', 1, 'q_a'),
                 '0': ('0', 1, 'q_a'),
                 ' ': ('A', -1, 'q_rv')
                 },
         'q_b': {'a': ('a', 1, 'q_b'),
                 'b': ('b', 1, 'q_b'),
                 'c': ('c', 1, 'q_b'),
                 'A': ('A', 1, 'q_b'),
                 'B': ('B', 1, 'q_b'),
                 'C': ('C', 1, 'q_b'),
                 '0': ('0', 1, 'q_b'),
                 ' ': ('B', -1, 'q_rv')
                 },
         'q_c': {'a': ('a', 1, 'q_c'),
                 'b': ('b', 1, 'q_c'),
                 'c': ('c', 1, 'q_c'),
                 'A': ('A', 1, 'q_c'),
                 'B': ('B', 1, 'q_c'),
                 'C': ('C', 1, 'q_c'),
                 '0': ('0', 1, 'q_c'),
                 ' ': ('C', -1, 'q_rv')
                 },
         'q_end': {'0': (' ', 1, 'q_end'),
                   'A': ('a', 1, 'q_end'),
                   'B': ('b', 1, 'q_end'),
                   'C': ('c', 1, 'q_end'),
                   ' ': (' ', 0, 'qT')
                   }
         }

tape = list(input())
tape += [' ' for x in range(14)]
tape = [' '] + tape
tape += [' ']
index = 0
state = 'q_start'

while state != 'qT':
    symb = tape[index]

    new_symb, movement, state = table[state][symb]

    tape[index] = new_symb
    index += movement

print(''.join(tape).replace(' ', ''))

