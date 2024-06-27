i = 0
s = 0

l = list(input())

while(True):
    if(s == 0): #find first 'a'
        if(l[i] == 'a'): s = 1
        i += 1
    elif(s == 1): #go to next state according to current char
        if(l[i] in ['a', ' ']): s = 2
        elif(l[i] == 'b'):      s = 3
        elif(l[i] == 'c'):      s = 4
        i -= 1

    elif(s in [2, 3, 4]): #skip left to first char
        if(l[i] != ' '): i -= 1
        else:
            i += 1
            s += 3

    elif(s in [5, 6, 7]): #skip right to first 'c'
        if(l[i] != 'c'): i += 1
        else:
            i -= 1
            s += 3

    elif(s in [8, 9, 10]): #replace char
        l[i] = 'abc'[s-8]
        s = 11

    elif(s == 11):
        break

print("".join(l))
