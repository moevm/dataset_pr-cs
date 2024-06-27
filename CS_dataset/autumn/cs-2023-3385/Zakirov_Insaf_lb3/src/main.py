TM = {
    'q1' : {
        'a' : ['a', 1, 'q2'],
        'b' : ['b', 1, 'q3'],
        'c' : ['c', 1, 'q2'],
        ' ' : [' ', 1, 'q1']
    },
    
    'q2' : {
        'a' : ['a', 1, 'q2'],
        'b' : ['b', 1, 'q3'],
        'c' : ['c', 1, 'q2'],
        ' ' : [' ',-1, 'q12']
    },
    
    'q3' : {
        'a' : ['a', 1, 'q4'],
        'b' : ['a', 1, 'q4'],
        'c' : ['a', 1, 'q4'],
        ' ' : [' ',-1, 'q11']
    },
    
    'q4' : {
        'a' : ['b', 1, 'q5'],
        'b' : ['b', 1, 'q5'],
        'c' : ['b', 1, 'q5'],
        ' ' : [' ',-1, 'q10']
    },
    
    'q5' : {
        'a' : ['b', -1, 'q6'],
        'b' : ['b', -1, 'q8'],
        'c' : ['b', -1, 'q9'],
        ' ' : [' ', -1, 'q10']
    },
    
    'q6' : {
        'a' : ['a', 1, 'q7'],
        'b' : ['a',-1, 'q6'],
    },
    
    'q7' : {
        'a' : ['a', 1, 'q7'],
        'b' : ['b', 1, 'q5'],
    },
    
    'q8' : {
        'a' : ['b', 1, 'q7'],
        'b' : ['a',-1, 'q8'],
    },
    
    'q9' : {
        'a' : ['c', 1, 'q7'],
        'b' : ['a',-1, 'q9'],
    },
    
    'q10' : {
        'a' : [' ', 0, 'qT'],
        'b' : [' ',-1, 'q10'],
    },
    
    'q11' : {
        'b' : [' ', 0, 'qT'],
    },
    
    'q12' : {
        'a' : ['a',-1, 'q12'],
        'c' : ['c',-1, 'q12'],
        ' ' : [' ', 1, 'q13']
    },
    
    'q13' : {
        'a' : [' ', 0, 'qT'],
        'c' : [' ', 0, 'qT'],
    }

}

s = list(input())

q = 'q1'
i = 0

while (q != 'qT') :
    s[i], w, q = TM[q][s[i]]
    i += w
    
print("".join(s))
