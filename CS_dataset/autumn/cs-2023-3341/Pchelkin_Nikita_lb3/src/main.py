moves = {'R': 1, 'L': -1, 'N': 0}

tab = {
    'qn' : {'a': ('a', 'R', 'q1'),
            'b': ('b', 'R', 'q0'),
            'c': ('c', 'R', 'q0'),
            ' ': (' ', 'R', 'qn')
           },
    'q0' : {'a': ('a', 'R', 'q1'),
            'b': ('b', 'R', 'q0'),
            'c': ('c', 'R', 'q0'),
            ' ': (' ', 'N', 'qT')
           },
    'q1' : {'a': ('a', 'L', 'q1a'),
            'b': ('b', 'L', 'q1b'),
            'c': ('c', 'L', 'q1c'),
            ' ': (' ', 'L', 'q1a')
           },
    'q1a' : {'a': ('a', 'L', 'q1a'),
             'b': ('b', 'L', 'q1a'),
             'c': ('c', 'L', 'q1a'),
             ' ': (' ', 'R', 'q2a')
           },
    'q2a': {'a': ('a', 'R', 'q2a'),
            'b': ('b', 'R', 'q2a'),
            'c': ('c', 'L', 'q3a'),
            ' ': (' ', 'N', 'qT')
            },
    'q3a': {'a': ('a', 'N', 'qT'),
            'b': ('a', 'N', 'qT'),
            'c': ('a', 'N', 'qT'),
            ' ': ('a', 'N', 'qT')
            },
    'q1b': {'a': ('a', 'L', 'q1b'),
            'b': ('b', 'L', 'q1b'),
            'c': ('c', 'L', 'q1b'),
            ' ': (' ', 'R', 'q2b')
            },
    'q2b': {'a': ('a', 'R', 'q2b'),
            'b': ('b', 'R', 'q2b'),
            'c': ('c', 'L', 'q3b'),
            ' ': (' ', 'N', 'qT')
            },
    'q3b': {'a': ('b', 'N', 'qT'),
            'b': ('b', 'N', 'qT'),
            'c': ('b', 'N', 'qT'),
            ' ': ('b', 'N', 'qT')
            },
    'q1c': {'a': ('a', 'L', 'q1c'),
            'b': ('b', 'L', 'q1c'),
            'c': ('c', 'L', 'q1c'),
            ' ': (' ', 'R', 'q2c')
            },
    'q2c': {'a': ('a', 'R', 'q2c'),
            'b': ('b', 'R', 'q2c'),
            'c': ('c', 'L', 'q3c'),
            ' ': (' ', 'N', 'qT')
            },
    'q3c': {'a': ('c', 'N', 'qT'),
            'b': ('c', 'N', 'qT'),
            'c': ('c', 'N', 'qT'),
            ' ': ('c', 'N', 'qT')
            },
}

tape = list("  " + input() + "  ")
index = 0
state = 'qn'

while(state != 'qT'):
    char = tape[index]
    new_char, move, new_state = tab[state][char]

    tape[index] = new_char
    index += moves[move]
    state = new_state

print(''.join(tape).lstrip().rstrip())
