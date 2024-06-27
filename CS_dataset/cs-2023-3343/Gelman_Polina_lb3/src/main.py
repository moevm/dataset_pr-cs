R, L, N = 1, -1, 0
t = {
    'q0':{'a': ('a', R, 'q0'), 
          'b': ('b', R, 'q0'), 
          'c': ('c', R, 'q0'), 
          ' ': (' ', L, 'q1')},
    
    'q1':{'a': ('a', L, 'q2'), 
          'b': ('b', L, 'q2'), 
          'c': ('c', L, 'q2'), 
          ' ': (' ', L, 'q1')}, # скип ласт букву
    
    'q2': {'a': ('-', R, 'q3'), 
           'b': ('-', R, 'q4'), 
           'c': ('-', R, 'q5'), 
           '-' : ('-', L, 'q2'), 
           ' ': (' ', R, 'q7')},
    #a
    'q3':{'a': ('a', R, 'q3'), 
          'b': ('b', R, 'q3'), 
          'c': ('c', R, 'q3'), 
          '-': ('-', R, 'q3'), 
          ' ': ('a', L, 'q6')},
    #b
    'q4': {'a': ('a', R, 'q4'), 
           'b': ('b', R, 'q4'), 
           'c': ('c', R, 'q4'), 
           '-': ('-', R, 'q4'), 
           ' ': ('b', L, 'q6')},
    #c
    'q5': {'a': ('a', R, 'q5'), 
           'b': ('b', R, 'q5'), 
           'c': ('c', R, 'q5'),
           '-': ('-', R, 'q5'), 
           ' ': ('c', L, 'q6'), 
           },


    'q6': {'a': ('a', L, 'q6'), 
           'b': ('b', L, 'q6'), 
           'c': ('c', L, 'q6'), 
           '-': ('-', N, 'q2')},
    
    'q7': {'a' : ('a', R, 'q7'), 
           'b' : ('b', R, 'q7'), 
           'c' : ('c', R, 'q7'), 
           '-': (' ', R, 'q7'), 
           ' ': (' ',N, 'qT')}
}
s = input()
lenta = list(' '*100 + s + ' '*100)
state = 'q0'
index = 0
states = [state]

while state != 'qT':
    curr = lenta[index]
    next = t[state][curr]
    lenta[index] = next[0]
    index += next[1]
    state = next[2]
    states += [state]
s = ''
for i in lenta:
    s += i
print(s)
