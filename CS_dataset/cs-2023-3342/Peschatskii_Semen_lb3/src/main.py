table={
    'q0':{'a': ('a',1,'q1'), 'b': ('b',1,'q1'), 'c': ('c',1,'q1'), ' ': (' ',1,'q0')},
    'q1':{'a': ('a',1,'q1'), 'b': ('b',1,'q1'), 'c': ('c',1,'q1'), ' ': (' ',-1,'q2')},
    'q2':{'a': ('a',-1,'q3'),'b': ('b',-1,'q2'),'c': ('c',-1,'q2')},
    'q3':{'a': ('a',-1,'q4'),'b': ('b',-1,'q2'),'c': ('c',-1,'q2')},
    'q4':{'a': ('a',1,'q5'), 'b': ('b',1,'q6'), 'c': ('c',1,'q7')},
    'q5':{'a': ('a',1,'q5'), 'b': ('a',0,'qt'), 'c': ('a',0,'qt'), ' ': ('a',0,'qt')},
    'q6':{'a': ('a',1,'q6'), 'b': ('b',0,'qt'), 'c': ('b',0,'qt'), ' ': ('b',0,'qt')},
    'q7':{'a': ('a',1,'q7'), 'b': ('c',0,'qt'), 'c': ('c',0,'qt'), ' ': ('c',0,'qt')},
}

memory = list(input())
pos = 0
state = 'q0'
while(state != 'qt'):
    memory[pos], d, state = table[state][memory[pos]]
    pos += d

print(''.join(memory), sep='\n') 