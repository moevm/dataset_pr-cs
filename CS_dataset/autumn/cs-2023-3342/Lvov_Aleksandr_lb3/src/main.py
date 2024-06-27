STATES = {'q1': {' ': (' ', 1, 'q1'),
                 'a': ('a', 1, 'q2'),
                 'b': ('b', 1, 'q2'),
                 'c': ('c', 1, 'q2')},
          'q2': {' ': (' ', 0, 'q3'),
                 'a': ('a', 1, 'q2'),
                 'b': ('b', 1, 'q2'),
                 'c': ('c', 1, 'q2')},
          'q3': {' ': (' ', -1, 'q3'),
                 'a': ('a', -1, 'q4'),
                 'b': ('b', -1, 'q3'),
                 'c': ('c', -1, 'q3')},
          'q4': {' ': (' ', -1, 'q3'),
                 'a': ('a', -1, 'q5'),
                 'b': ('b', -1, 'q3'),
                 'c': ('c', -1, 'q3')},
          'q5': {' ': (' ', 3, 'qt'),
                 'a': ('a', 3, 'q6'), 
                 'b': ('b', 3, 'q7'),
                 'c': ('c', 3, 'q8')},
          'q6': {' ': ('a', 0, 'qt'),
                 'a': ('a', 0, 'qt'),
                 'b': ('a', 0, 'qt'),
                 'c': ('a', 0, 'qt')},
          'q7': {' ': ('b', 0, 'qt'),
                 'a': ('b', 0, 'qt'),
                 'b': ('b', 0, 'qt'),
                 'c': ('b', 0, 'qt')},
          'q8': {' ': ('c', 0, 'qt'),
                 'a': ('c', 0, 'qt'),
                 'b': ('c', 0, 'qt'),
                 'c': ('c', 0, 'qt')},
          'qt': {' ': (' ', 0, 'qt'),
                 'a': (' ', 0, 'qt'),
                 'b': (' ', 0, 'qt'),
                 'c': (' ', 0, 'qt')},
          }

state = 'q1'
index = 0
memory = list(' ') + list(input()) + list(' ')
while state != 'qt':
    char = memory[index]
    memory[index] = STATES[state][char][0]
    index += STATES[state][char][1]
    state = STATES[state][char][2]
print(''.join(memory))

