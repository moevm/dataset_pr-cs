string = input() + ' '*13
memory = list(string)
index = 0
state = 'q0'

table = {
    'q0': {
        'a': ('a', 1, 'q1'),
        'b': ('b', 1, 'q1'),
        'c': ('c', 1, 'q1'),
        ' ': (' ', 1, 'q0')
    },
    'q1': {
        'a': ('a', 1, 'q1'),
        'b': ('b', 1, 'q1'),
        'c': ('c', 1, 'q1'),
        ' ': (' ', -1, 'q2'),
    },
    'q2': {
        'a': ('D', 1, 'q3'),
        'b': ('D', 1, 'q4'),
        'c': ('D', 1, 'q5'),
        ' ': (' ', 1, 'q7'),
        'D': ('D', -1, 'q2'),
    },
    'q3': {
        'a': ('a', 1, 'q3'),
        'b': ('b', 1, 'q3'),
        'c': ('c', 1, 'q3'),
        ' ': ('a', -1, 'q6'),
        'D': ('D', 1, 'q3'),
    },
    'q4': {
        'a': ('a', 1, 'q4'),
        'b': ('b', 1, 'q4'),
        'c': ('c', 1, 'q4'),
        ' ': ('b', -1, 'q6'),
        'D': ('D', 1, 'q4'),
    },
    'q5': {
        'a': ('a', 1, 'q5'),
        'b': ('b', 1, 'q5'),
        'c': ('c', 1, 'q5'),
        ' ': ('c', -1, 'q6'),
        'D': ('D', 1, 'q5'),
    },
    'q6': {
        'a': ('a', -1, 'q6'),
        'b': ('b', -1, 'q6'),
        'c': ('c', -1, 'q6'),
        'D': ('D', -1, 'q2'),
    },
    'q7': {
        'a': ('a', 0, 'qt'),
        'b': ('b', 0, 'qt'),
        'c': ('c', 0, 'qt'),
        'D': (' ', 1, 'q7'),
    },
}

while state != 'qt':
    symbol = memory[index]
    new_symbol, delta, state = table[state][symbol]
    memory[index] = new_symbol
    index+=delta

print(''.join(memory).replace(' ', ''))
