R, N, L = 1, 0, -1
turing = {
    'q1': {'a': ['a', R, 'q2'], 'b': ['b', R, 'q3'], 'c': ['c', R, 'q2'], ' ': [' ', R, 'q1']},
    'q2': {'a': ['a', R, 'q2'], 'b': ['b', R, 'q3'], 'c': ['c', R, 'q2'], ' ': [' ', L, 'q4']},
    'q3': {'a': ['', R, 'q5'], 'b': ['', R, 'q5'], 'c': ['', R, 'q5'], ' ': [' ', L, 'q5']},
    'q4': {'a': ['a', L, 'q4'], 'c': ['c', L, 'q4'], ' ': [' ', R, 'q5']},
    'q5': {'a': ['', N, 'q0'], 'b': ['', N, 'q0'], 'c': ['', N, 'q0'], ' ': [' ', N, 'q0']}
}
string = list(input())
q = 'q1'
index = 0
while q != 'q0':
    s, mov, sost = turing[q][string[index]]
    string[index] = s
    index += mov
    q = sost
print(''.join(string))