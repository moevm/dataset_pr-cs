memory = list(input())
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
        ' ': (' ', -1, 'q2')
    },
    'q2': {
        'a': ('a', -1, 'q3'),
        'b': ('b', -1, 'q2'),
        'c': ('c', -1, 'q2'),
        ' ': (' ', 0, 'q2')
    },
    'q3': {
        'a': ('a', -1, 'q4'),
        'b': ('b', -1, 'q2'),
        'c': ('c', -1, 'q2'),
        ' ': (' ', 0, 'qT')
    },
    'q4': {
        'a': ('a', 1, 'q5'),
        'b': ('b', 1, 'q6'),
        'c': ('c', 1, 'q7'),
        ' ': (' ', 0, 'qT')
    },
    'q5': {
        'a': ('a', 1, 'q5'),
        'b': ('a', 0, 'qT'),
        'c': ('a', 0, 'qT'),
        ' ': ('a', 0, 'qT')
    },
    'q6': {
        'a': ('a', 1, 'q6'),
        'b': ('b', 0, 'qT'),
        'c': ('b', 0, 'qT'),
        ' ': ('b', 0, 'qT')
    },
    'q7': {
        'a': ('a', 1, 'q7'),
        'b': ('c', 0, 'qT'),
        'c': ('c', 0, 'qT'),
        ' ': ('c', 0, 'qT')
    },
}
while state != 'qT':
    symbol = memory[index]
    new_symbol, delta, state = table[state][symbol]
    memory[index] = new_symbol
    index += delta
print(''.join(memory))