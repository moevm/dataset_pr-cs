index = 0
end = 0
memory = list(input())

while(True):
    if(end == 0): 
        if(memory[index] == 'a'): end = 1
        index += 1
    elif(end == 1): 
        if(memory[index] in ['a', ' ']): end = 2
        elif(memory[index] == 'b'):      end = 3
        elif(memory[index] == 'c'):      end = 4
        index -= 1
    elif(end in [2, 3, 4]): 
        if(memory[index] != ' '): index -= 1
        else:
            index += 1
            end += 3
    elif(end in [5, 6, 7]): 
        if(memory[index] != 'c'): index += 1
        else:
            index -= 1
            end += 3
    elif(end in [8, 9, 10]): 
        memory[index] = 'abc'[end-8]
        end = 11
    elif(end == 11):
        break

print("".join(memory))
