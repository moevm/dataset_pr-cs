table = {
    'q0':{
        'a':('a',1,'q0'),
        'b':('b',1,'q1'),
        'c':('c',1,'q0'),
        ' ':(' ',1,'q0'),
        },
    'q1':{
        'a':('',1,'q2'),
        'b':('',1,'q2'),
        'c':('',1,'q2'),
        ' ':('',-1,'q3'),
        },
    'q2':{
        'a':('',0,'q4'),
        'b':('',0,'q4'),
        'c':('',0,'q4'),
        ' ':('',0,'q4'),
        },
    'q3':{
        'b':('',0,'q4'),
        },
    }

memory = list(input())
index = 0
state = 'q0'

while(state!='q4' and index<len(memory)):
    symbol = memory[index]
    new_symbol,delta,state = table[state][symbol]
    memory[index] = new_symbol
    index+=delta

if(state == 'q0'):
    for i in range(0,len(memory)):
        if(memory[i]!=' '):
            memory[i] = ''
            break

print(''.join(memory))
