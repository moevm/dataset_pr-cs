L, R, N = -1, 1, 0
table = {
    'q0': {'a': ['a', R, 'q1'], 'b': ['b', R, 'q1'], 'c': ['c', R, 'q1'], ' ': [' ', R, 'q0']},  
    'q1': {'a': ['a', R, 'q1'], 'b': ['b', R, 'q1'], 'c': ['c', R, 'q1'], ' ': [' ', L, 'q2']},  
    'q2': {'a': ['a', L, 'q3'], 'b': ['b', L, 'q2'], 'c': ['c', L, 'q2']},  
    'q3': {'a': ['a', L, 'q4'], 'b': ['b', L, 'q2'], 'c': ['c', L, 'q2']},  
    'q4': {'a': ['a', R, 'q5'], 'b': ['b', R, 'q6'], 'c': ['c', R, 'q7']},  
    'q5': {'a': ['a', R, 'q5'], 'b': ['a', N, 'qT'], 'c': ['a', N, 'qT'], ' ': ['a', N, 'qT']}, 
    'q6': {'a': ['a', R, 'q6'], 'b': ['b', N, 'qT'], 'c': ['b', N, 'qT'], ' ': ['b', N, 'qT']}, 
    'q7': {'a': ['a', R, 'q7'], 'b': ['c', N, 'qT'], 'c': ['c', N, 'qT'], ' ': ['c', N, 'qT']}   
}
memory = list(input())
q = 'q0'
index = -1
states = [q]
while q != 'qT':
    symb = memory[index]
    symbol, i, q = table[q][symb]
    memory[index] = symbol
    index += i
    states.append(q)
print(*memory, sep='')
