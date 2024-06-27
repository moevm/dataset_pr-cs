L, N, R = -1,0,1
state_table = {'q1': {'a':['a',R,'q2'],'b':['b',R,'q2'],'c':['c',R,'q2'],' ':[' ',R,'q1']},
         'q2': {'a':['a',R,'q2'],'b':['b',R,'q2'],'c':['c',R,'q2'],' ':[' ',N,'q3']},
         'q3': {'a':['d',N,'q4'],'b':['d',N,'q6'],'c':['d',N,'q8'],' ':[' ',L,'q3']},
         'q4': {'a':['a',R,'q4'],'b':['b',R,'q4'],'c':['c',R,'q4'],'d':['d',R,'q4'],' ':[' ',R,'q5']},
         'q5': {'a':['a',R,'q5'],'b':['b',R,'q5'],'c':['c',R,'q5'],' ':['a',L,'q10']},
         'q6': {'a':['a',R,'q6'],'b':['b',R,'q6'],'c':['c',R,'q6'],'d':['d',R,'q6'],' ':[' ',R,'q7']},
         'q7': {'a':['a',R,'q7'],'b':['b',R,'q7'],'c':['c',R,'q7'],' ':['b',L,'q10']},
         'q8': {'a':['a',R,'q8'],'b':['b',R,'q8'],'c':['c',R,'q8'],'d':['d',R,'q8'],' ':[' ',R,'q9']},
         'q9': {'a':['a',R,'q9'],'b':['b',R,'q9'],'c':['c',R,'q9'],' ':['c',L,'q10']},
         'q10': {'a':['a',L,'q10'],'b':['b',L,'q10'],'c':['c',L,'q10'],' ':[' ',L,'q11']},
         'q11': {'a':['d',N,'q4'],'b':['d',N,'q6'],'c':['d',N,'q8'],'d':['d',L,'q11'],' ':[' ',R,'q12']},
         'q12': {'d':[' ',R,'q12'],' ':[' ',N,'end']}}

array = list(input())
state = 'q1'
index = 0
spaces = list(' '*20)
array = spaces + array + spaces

while state != 'end':
    dictionary = state_table[state][array[index]]
    array[index] = dictionary[0]
    index += dictionary[1]
    state = dictionary[2]

print(*array, sep='')