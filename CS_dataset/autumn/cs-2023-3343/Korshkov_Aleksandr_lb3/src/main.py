memory = list(input())
q = "q0"
idx = 0

while q != "qT":
    if q == "q0":
        if memory[idx] == "b":
            idx += 1
            q = "q2"
        elif memory[idx] != " ":
            idx += 1
            q = "q1"
        else:
            idx += 1
    elif q == "q1":
        if memory[idx] == "b":
            idx += 1
            q = "q2"
        elif memory[idx] == " ":
            idx -= 1
            q = "qDs"
        else:
            idx += 1
    elif q == "q2":
        if memory[idx] == " ":
            idx -= 1
            q = "qD"
        else:
            memory[idx] = " "
            idx += 1
            q = "q2.1"
    elif q == "q2.1":
        memory[idx] = " "
        idx += 1
        q = "qS"
    elif q == "qS":
        if memory[idx] == " ":
            q = "qT"
        elif memory[idx] == "a":
            memory[idx] = " "
            idx -= 1
            q = "qA"
        elif memory[idx] == "b":
            memory[idx] = " "
            idx -= 1
            q = "qB"
        elif memory[idx] == "c":
            memory[idx] = " "
            idx -= 1
            q = "qC"
    elif q == "qA" or q == "qB" or q == "qC":
        idx -= 1
        q = q + "1"
    elif q == "qA1":
        memory[idx] = "a"
        idx += 1
        q = "qP"
    elif q == "qB1":
        memory[idx] = "b"
        idx += 1
        q = "qP"
    elif q == "qC1":
        memory[idx] = "c"
        idx += 1
        q = "qP"
    elif q == "qP":
        idx += 1
        q = "qP1"
    elif q == "qP1":
        idx += 1
        q = "qS"
    elif q == "qDs":
        if memory[idx] != " ":
            idx -= 1
        else:
            idx += 1
            q = "qD"
    elif q == "qD":
        memory[idx] = " "
        q = "qT"
print("".join(memory))
