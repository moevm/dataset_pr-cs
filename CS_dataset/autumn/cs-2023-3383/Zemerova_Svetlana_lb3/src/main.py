memory=list(input())
states={
'q1':{' ':[' ',1,'q1'], 'b':['b',1,'q1'], 'a':['a',1,'q2'], 'c':['c',1,'q5']},
'q2':{'a':['a',1,'q3'], 'b':['b',1,'q4'], 'c':['c',-1,'q15']},
'q3':{'a':['a',1,'q3'], 'b':['b',1,'q3'], 'c':['c',-1,'q13']},
'q4':{'a':['a',1,'q4'], 'b':['b',1,'q4'], 'c':['c',-1,'q14']},


'q5':{'a':['a',1,'q6'], 'b':['b',1,'q5'], 'c':['c',1,'q5']},
'q6':{'a':['a',-1,'q7'], 'b':['b',-1,'q8'], 'c':['c',-1,'q9'], ' ':[' ',-1,'q7']},

'q7':{'a':['a',-1,'q7'], 'b':['b',-1,'q7'], 'c':['c',-1,'q7'], ' ':[' ',1,'q10']},
'q8':{'a':['a',-1,'q8'], 'b':['b',-1,'q8'], 'c':['c',-1,'q8'], ' ':[' ',1,'q11']},
'q9':{'a':['a',-1,'q9'], 'b':['b',-1,'q9'], 'c':['c',-1,'q9'], ' ':[' ',1,'q12']},

'q10':{'a':['a',1,'q10'], 'b':['b',1,'q10'], 'c':['c',-1,'q13']},
'q11':{'a':['a',1,'q11'], 'b':['b',1,'q11'], 'c':['c',-1,'q14']},
'q12':{'a':['a',1,'q12'], 'b':['b',1,'q12'], 'c':['c',-1,'q15']},

'q13':{'a':['a',0,'qT'], 'b':['a',0,'qT'], 'c':['a',0,'qT'], ' ':['a',0,'qT']},
'q14':{'a':['b',0,'qT'], 'b':['b',0,'qT'], 'c':['b',0,'qT'], ' ':['b',0,'qT']},
'q15':{'a':['c',0,'qT'], 'b':['c',0,'qT'], 'c':['c',0,'qT'], ' ':['c',0,'qT']}
}
ind=0
q='q1'

while (q!='qT'):
    symbol,direction,state=states[q][memory[ind]]
    memory[ind]=symbol
    ind+=direction
    q=state
    
print(''.join(memory))
