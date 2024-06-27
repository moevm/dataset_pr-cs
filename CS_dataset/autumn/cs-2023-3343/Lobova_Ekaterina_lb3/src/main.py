L, R, N = -1, 1, 0

table = {'q1':{'a':['a', R, 'q2'], 'b': ['b', R, 'q1'], 'c': ['c', R, 'q1'], ' ':[' ', R, 'q1']},
         'q2':{'a':['a', L, 'q3'], 'b': ['b', L, 'q4'], 'c': ['c', L, 'q5'], ' ':[' ', L, 'q3']},
         
         'q3':{'a':['a', L, 'q3'], 'b': ['b', L, 'q3'], 'c': ['c', L, 'q3'], ' ': [' ', R, 'q9']},
         'q4':{'a':['a', L, 'q4'], 'b': ['b', L, 'q4'], 'c': ['c', L, 'q4'], ' ': [' ', R, 'q10']},
         'q5':{'a':['a', L, 'q5'], 'b': ['b', L, 'q5'], 'c': ['c', L, 'q5'], ' ': [' ', R, 'q11']},
         
         'q6':{'a':['a', N, 'qT'], 'b': ['a', N, 'qT'], 'c': ['a', N, 'qT'], ' ': ['a', N, 'qT']},
         'q7':{'a':['b', N, 'qT'], 'b': ['b', N, 'qT'], 'c': ['b', N, 'qT'], ' ': ['b', N, 'qT']},
         'q8':{'a':['c', N, 'qT'], 'b': ['c', N, 'qT'], 'c': ['c', N, 'qT'], ' ': ['c', N, 'qT']},
         
         'q9':{'a':['a', R, 'q9'], 'b': ['b', R, 'q9'], 'c': ['c', L, 'q6']},
         'q10':{'a':['a', R, 'q10'], 'b': ['b', R, 'q10'], 'c': ['c', L, 'q7']},
         'q11':{'a':['a', R, 'q11'], 'b': ['b', R, 'q11'], 'c': ['c', L, 'q8']}}
        
memory = list(input())
state = 'q1'
index = 0

while state != 'qT':
    current_symbol = memory[index]
    future = table[state][current_symbol]
    memory[index] = future[0]
    index += future[1]
    state = future[2]

print(*memory, sep='')
