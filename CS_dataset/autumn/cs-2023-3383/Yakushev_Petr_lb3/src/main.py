R,N,L=1,0,-1
lnt = list(input())
state = 'q0'
i = len(lnt) - 1
states = {
    'q0': {'a': ['a', L, 'q1'], 'b': ['b',L, 'q0'], 'c': ['c', L, 'q0'], ' ': [' ', L, 'q0']},
    'q1': {'a': ['a', L, 'qaL'], 'b': ['b', L, 'q0'], 'c': ['c', L, 'q0'], ' ': [' ', N, 'q2']},
    'qaL': {'a': ['a', R, 'qaa'], 'b': ['b', R, 'qba'], 'c': ['c', R, 'qca'], ' ': [' ', N, 'q2']},
    'qaa': {'a': ['a', R, 'qaa'], 'b': ['a', N, 'q2'], 'c': ['a', N, 'q2'], ' ': ['a', N, 'q2']},
    'qba': {'a': ['a', R, 'qba'], 'b': ['b', N, 'q2'], 'c': ['b', N, 'q2'], ' ': ['b', N, 'q2']},
    'qca': {'a': ['a', R, 'qca'], 'b': ['c', N, 'q2'], 'c': ['c', N, 'q2'], ' ': ['c', N, 'q2']}
}
while state != 'q2' and i >= 0:
    s = lnt[i]

    s2 = states[state][s]
    lnt[i] = s2[0]
    i += s2[1]  
    state = s2[2]

print(''.join(lnt))
