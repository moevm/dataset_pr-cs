tape = list(input())

pos = 0
state = 0

charset = { 'a': 0, 'b': 1, 'c': 2, ' ': 3 }
states = [
#   'a'              'b'             'c'             ' '
    [('a', +1, 1),   ('b', +1, 1),   ('c', +1, 1),   (' ', +1, 0)], # 0
    [('a', +1, 1),   ('b', +1, 1),   ('c', +1, 1),   (' ', -1, 2)], # 1
    [('a', -1, 3),   ('b', -1, 2),   ('c', -1, 2),   (' ',  0, 9)], # 2
    [('a', -1, 4),   ('b', -1, 2),   ('c', -1, 2),   (' ',  0, 9)], # 3
    [('a', +1, 5),   ('b', +1, 6),   ('c', +1, 7),   (' ', +1, 8)], # 4
    [('a', +1, 5),   ('a',  0, 9),   ('a',  0, 9),   ('a',  0, 9)], # 5
    [('a', +1, 6),   ('b',  0, 9),   ('b',  0, 9),   ('b',  0, 9)], # 6
    [('a', +1, 7),   ('c',  0, 9),   ('c',  0, 9),   ('c',  0, 9)], # 7
    [('a', +1, 8),   (' ',  0, 9),   (' ',  0, 9),   (' ',  0, 9)], # 8
]

while state != 9:
    if pos >= len(tape) or pos < 0:
        print(f'out of range. pos = {pos}')
        exit()

    if not (tape[pos] in charset):
        print(f'invalid character \'{tape[pos]}\'')
        exit()

    rule = states[state][charset[tape[pos]]]

    tape[pos] = rule[0]
    pos += rule[1]
    state = rule[2]

print(''.join(tape))