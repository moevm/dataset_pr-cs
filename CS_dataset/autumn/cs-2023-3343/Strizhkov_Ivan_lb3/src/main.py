L, R, N = -1, 1, 0

table = {
    'q1': {'a': ['a', R, 'q1_a'], 'b': ['b', R, 'q2'], 'c': ['c', R, 'q1_a'], ' ': [' ', R, 'q1']},
    'q1_a': {'a': ['a', R, 'q1_a'], 'b': ['b', R, 'q2'], 'c': ['c', R, 'q1_a'], ' ': ['', L, 'q6']},
    'q2': {'a': ['', R, 'q3'], 'b': ['', R, 'q3'], 'c': ['', R, 'q3'], ' ': ['', L, 'q4']},
    'q3': {'a': ['', R, 'q5'], 'b': ['', R, 'q5'], 'c': ['', R, 'q5'], ' ': ['', N, 'qT']},
    'q4': {'a': ['', N, 'qT'], 'b': ['', N, 'qT'], 'c': ['', N, 'qT']},
    'q5': {'a': ['a', R, 'q5'], 'b': ['b', R, 'q5'], 'c': ['c', R, 'q5'], ' ': ['', R, 'qT']},
    'q6': {'a': ['a', L, 'q6'], 'b': ['b', L, 'q6'], 'c': ['c', L, 'q6'], ' ': ['', R, 'q4']},
}

table_now = 'q1'
count = 1
result = list(' ' + input().strip() + ' ')
while table_now != 'qT':
       symbol = result[count]
       result[count] = table[table_now][symbol][0]
       count += table[table_now][symbol][1]
       table_now = table[table_now][symbol][2]
print(''.join(result))