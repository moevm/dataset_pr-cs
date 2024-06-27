stri = list(input())
states = ['q0', 'q1', 'q2', 'q3', 'q4', 'q5', 'q6', 'q7', 'q8', 'q9', 'q10', 'q11', 'q12', 'q13', 'q14', 'q15', 'q16', 'q17', 'q18']
end = states[18]
state = states[0]
index = 0

while True:
    if state == end:
        break

    elif state == states[0]: 
        if stri[index] == ' ':
            index += 1
            state = states[0]
        elif stri[index] in 'abc':
            state = states[1]

    elif state == states[1]:
        if stri[index] == ' ':
            index += -1
            state = states[13]
        elif stri[index] in 'ac':
            index += 1
            state = states[1]
        elif stri[index] == 'b':
            index += 1
            state = states[15]
    
    elif state == states[2]:
        if stri[index] == ' ':
            index += -1
            state = states[17]
        elif stri[index] in 'abc':
            index += 1
            state = states[3]

    elif state == states[3]:
        if stri[index] == ' ':
            index += -1
            state = states[11]
        elif stri[index] == 'a':
            index += -1
            state = states[4]
        elif stri[index] == 'b':
            index += -1
            state = states[5]
        elif stri[index] == 'c':
            index += -1
            state = states[6]

    elif state == states[4]:
        if stri[index] == ' ':
            state = end
        elif stri[index] in 'abc':
            index += -1
            state = states[7]

    elif state == states[5]:
        if stri[index] == ' ':
            state = end
        elif stri[index] in 'abc':
            index += -1
            state = states[8]
        
    elif state == states[6]:
        if stri[index] == ' ':
            state = end
        elif stri[index] in 'abc':
            index += -1
            state = states[9]

    elif state == states[7]:
        if stri[index] == ' ':
            state = end
        elif stri[index] in 'abc':
            stri[index] = 'a'
            index += 1
            state = 'q10'

    elif state == states[8]:
        if stri[index] == ' ':
           state = end
        elif stri[index] in 'abc':
            stri[index] = 'b'
            index += 1
            state = states[10]

    elif state == states[9]:
        if stri[index] == ' ':
            state = end
        elif stri[index] in 'abc':
            stri[index] = 'c'
            index += 1
            state = states[10]

    elif state == states[10]:
        if stri[index] == ' ':
            index += -1
            state = states[11]
        elif stri[index] in 'ac':
            stri[index] = 'a'
            index += 1
            state = states[2]
        elif stri[index] == 'b':
            stri[index] = 'b'
            index += 1
            state = states[2]

    elif state == states[11]:
        if stri[index] == ' ':
            state = end
        elif stri[index] in 'abc':
            stri[index] = ''
            index += -1
            state = states[12]

    elif state == states[12]:
        if stri[index] == ' ':
            state = end
        elif stri[index] in 'abc':
            stri[index] = ''
            index += 1
            state = end

    elif state == states[13]:
        if stri[index] == ' ':
            state = states[14]
        elif stri[index] in 'abc':   
            index += -1
            state = states[13]

    elif state == states[14]:
        if stri[index] == ' ':
            index += 1
            stri[index] = ''
            state = end
        elif stri[index] in 'abc':
            stri[index] = ''
            index += 0
            state = end

    elif state == states[15]:
        if stri[index] == ' ':
            index += -1
            state = states[16]
        elif stri[index] in 'abc':
            index += 1
            state = states[2]

    elif state == states[16]:
        if stri[index] in 'abc ':
            stri[index] = ''
            index += 0
            state = end

    elif state == states[17]:
        if stri[index] in 'abc ':
            stri[index] = ''
            index += 0
            state = end
    
print(''.join(stri))