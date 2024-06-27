#MAIN

memory = list(input())

def main():
    global memory
    state = 'q1'
    i = 0
    while state != 'qend':
        memory, i, state = state_functions.get(state, lambda x, y: (x, y, state))(memory, i)
    memory = ''.join(memory)
    print(memory)

# STATES

def q1(memory, i):
    if memory[i] == 'b':
        return memory, i+1, 'q3'
    elif memory[i] == ' ':
        return memory, i+1, 'q1'
    else:
        return memory, i+1, 'q2'

def q2(memory, i):
    if memory[i] == 'b':
        return memory, i+1, 'q3'
    elif memory[i] == ' ':
        return memory, i-1, 'q4'
    else:
        return memory, i+1, 'q2'

def q3(memory, i):
    if memory[i] == ' ':
        return memory, i-1, 'q5'
    else:
        return memory, i+1, 'q7'

def q4(memory, i):
    if memory[i] == ' ':
        return memory, i+1, 'q5'
    else:
        return memory, i-1, 'q4'

def q5(memory, i):
    memory[i] = ' '
    return memory, i, 'qend'

def q7(memory, i):
    if memory[i] == ' ':
        return memory, i-1, 'q5'
    else:
        return memory, i+1, 'q9'

def q9(memory, i):
    if memory[i] == ' ':
        return memory, i-1, 'q10'
    else:
        return memory, i-1, 'q12'

def q10(memory, i):
    memory[i] = ' '
    return memory, i-1, 'q5'

def q12(memory, i):
    memory[i] = ' '
    return memory, i-1, 'q13'

def q13(memory, i):
    memory[i] = ' '
    return memory, i-1, 'q14'

def q14(memory, i):
    if memory[i] == 'b':
        memory[i] = ' '
        return memory, i+1, 'qb'
    if memory[i] == 'a':
        memory[i] = ' '
        return memory, i+1, 'qa'
    if memory[i] == 'c':
        memory[i] = ' '
        return memory, i+1, 'qc'
    if memory[i] == ' ':
        memory[i] = ' '
        return memory, i, 'qend'

def qb(memory, i):
    if memory[i] == ' ':
        return memory, i+1, 'qb'
    else:
        return memory, i-1, 'qbv'

def qbv(memory, i):
    memory[i] = 'b'
    return memory, i-1, 'qn1'

def qn1(memory, i):
    if memory[i] == ' ':
        return memory, i-1, 'qn2'
    else:
        return memory, i, 'q14'

def qn2(memory, i):
    if memory[i] == ' ':
        return memory, i-1, 'qn3'
    else:
        return memory, i, 'q14'

def qn3(memory, i):
    if memory[i] == ' ':
        return memory, i, 'qend'
    else:
        return memory, i, 'q14'

def qa(memory, i):
    if memory[i] == ' ':
        return memory, i+1, 'qa'
    else:
        return memory, i-1, 'qav'

def qav(memory, i):
    memory[i] = 'a'
    return memory, i-1, 'qn1'
    
def qc(memory, i):
    if memory[i] == ' ':
        return memory, i+1, 'qc'
    else:
        return memory, i-1, 'qcv'

def qcv(memory, i):
    memory[i] = 'c'
    return memory, i-1, 'qn1'

#DICT OF STATES NAME:FUNCTIONS

state_functions = {
    'q1': q1, 'q2': q2, 'q3': q3, 'q4': q4, 'q5': q5, 'q7': q7, 'q9': q9, 'q10': q10, 'q12': q12, 'q13': q13,
    'q14': q14, 'qa': qa, 'qb': qb, 'qc': qc, 'qav': qav, 'qbv': qbv,
    'qcv': qcv, 'qn1': qn1, 'qn2': qn2, 'qn3': qn3
}

#RUNNING

if __name__ == '__main__':
    main()
