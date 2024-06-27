L, R, N = -1, 1, 0
alf = {'q1': {'a': ['a', R, 'q1_a'], 'b': ['b', R, 'q2'], 'c': ['c', R, 'q1_a'], ' ': [' ', R, 'q1']},  # run to the first letter
       'q1_a': {'a': ['a', R, 'q1_a'], 'b': ['b', R, 'q2'], 'c': ['c', R, 'q1_a'], ' ': ['', L, 'q6']},  # run to the 'b'(q2) or last space(q6)
       'q2': {'a': ['', R, 'q3'], 'b': ['', R, 'q3'], 'c': ['', R, 'q3'], ' ': ['', L, 'q4']},  # delete first letter after 'b'
       'q3': {'a': ['', R, 'q5'], 'b': ['', R, 'q5'], 'c': ['', R, 'q5'], ' ': ['', N, 'qT']},  # delete second letter after 'b'
       'q4': {'a': ['', N, 'qT'], 'b': ['', N, 'qT'], 'c': ['', N, 'qT']},  # delete any letter
       'q5': {'a': ['a', R, 'q5'], 'b': ['b', R, 'q5'], 'c': ['c', R, 'q5'], ' ': ['', R, 'qT']},  # collect the rest of the word unchanged
       'q6': {'a': ['a', L, 'q6'], 'b': ['b', L, 'q6'], 'c': ['c', L, 'q6'], ' ': ['', R, 'q4']},  # run to the first space and delete the character to the right of it
       }

status = 'q1'
ct = 0
s = list(' ' + input() + ' ')
while status != 'qT':
       symbol = s[ct]
       s[ct] = alf[status][symbol][0]
       ct += alf[status][symbol][1]
       status = alf[status][symbol][2]
print(''.join(s))
