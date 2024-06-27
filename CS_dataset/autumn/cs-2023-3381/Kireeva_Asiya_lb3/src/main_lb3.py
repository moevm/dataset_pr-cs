s = list(input())
R, N, L = 1, 0, -1
state = 'q1'
index = 0
k = []
d = {
    'q1': {
        'a': ('a', R, 'q2'),
        'b': ('b', R, 'q3'),
        'c': ('c', R, 'q2'),
        ' ': (' ', R, 'q1')
    },
    'q2': {
        'a': ('a', R, 'q2'),
        'b': ('b', R, 'q3'),
        'c': ('c', R, 'q2'),
        ' ': (' ', L, 'q6')
    },
    'q3': {
        'a': ('', R, 'q4'),
        'b': ('', R, 'q4'),
        'c': ('', R, 'q4'),
        ' ': (' ', L, 'q5')
    },
    'q4': {
        'a': ('', N, 'q0'),
        'b': ('', N, 'q0'),
        'c': ('', N, 'q0'),
        ' ': (' ', L, 'q5')
    },
    'q5': {
        'a': ('', N, 'q0'),
        'b': ('', N, 'q0'),
        'c': ('', N, 'q0'),
        '': ('', N, 'q0')
    },
    'q6': {
        'a': ('a', L, 'q6'),
        'c': ('c', L, 'q6'),
        ' ': (' ', R, 'q7')
    },
    'q7': {
        'a': ('', N, 'q0'),
        'c': ('', N, 'q0'),
    }
}

while state != 'q0':
    symbol = s[index]
    s[index], delta, state = d[state][symbol]
    index += delta
    k.append(state)
print(''.join(s))
# print(*k)  # вывод списка изменений состояний