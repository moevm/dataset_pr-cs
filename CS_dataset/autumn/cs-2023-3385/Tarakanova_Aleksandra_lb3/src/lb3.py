table={
    'q0':{'a':['a', 1, 'q1'], 'b':['b', 1, 'q2'], 'c':['c', 1, 'q3'], ' ':[' ',1, 'q0']},
    'q1':{'a':['a', -1, 'q4'], 'b':['a', -1, 'q5'], 'c':['a', -1, 'q6'], ' ':['a', -1, 'q7']},
    'q2':{'a':['b', -1, 'q4'], 'b':['b', -1, 'q5'], 'c':['b', -1, 'q6'], ' ':['b', -1, 'q7']},
    'q3':{'a':['c', -1, 'q4'], 'b':['c', -1, 'q5'], 'c':['c', -1, 'q6'], ' ':['c', -1, 'q7']},
    'q4':{'a':['a', 1, 'q0'], 'b':['a', 1, 'q0'], 'c':['a', 1, 'q0'], ' ':['a',1, 'q0']},
    'q5':{'a':['b', 1, 'q0'], 'b':['b', 1, 'q0'], 'c':['b', 1, 'q0'], ' ':['b',1, 'q0']},
    'q6':{'a':['c', 1, 'q0'], 'b':['c', 1, 'q0'], 'c':['c', 1, 'q0'], ' ':['c',1, 'q0']},
    'q7':{'a':[' ', -1, 'q8'], 'b':[' ', -1, 'q8'], 'c':[' ', -1, 'q8'], ' ':[' ', -1, 'q10']},
    'q8':{'a':['a', -1, 'q8'], 'b':['b', -1, 'q8'], 'c':['c', -1, 'q8'], ' ':[' ', 1, 'q9']},
    'q9':{'a':['a', 1, 'q1'], 'b':['b', 1, 'q2'], 'c':['c', 1, 'q3'], ' ':[' ',1, 'q10']},
}

strok = list(input())
q = 'q0'
i = 0

while q != 'q10':
    s, mov, st = table[q][strok[i]]
    strok[i] = s
    i += mov
    q=st

print(''.join(strok))