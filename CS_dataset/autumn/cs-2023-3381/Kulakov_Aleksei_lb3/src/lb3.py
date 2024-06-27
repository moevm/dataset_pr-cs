s = input()
state = "0"
pstate = -1
pos = 0
while state != "end":
    if state == "0":
        if s[pos] == "a" or s[pos] == "b" or s[pos] == "c":
            state = "goR"
            pstate = ord(s[pos]) - ord('a')
        elif s[pos] == "d" or s[pos] == "e" or s[pos] == "f":
            state = "reloadL"
            pstate = 0
        else:
            pos+=1
    if state == "goR":
        if s[pos] == " " or ord(s[pos]) >= ord('d'):
            state = "setL"
            pos-=1
        else:
            pos+=1
    if state == "setL":
        state = "goL"
        pstateTMP = ord(s[pos]) - ord('a')
        s = s[:pos] + chr(ord('d') + pstate) + s[pos+1:]
        pstate = pstateTMP
        pos-=1
    if state == "goL":
        if s[pos] == " " or ord(s[pos]) >= ord('d'):
            state = "setR"
            pos+=1
        else:
            pos-=1
    if state == "setR":
        state = "0"
        s = s[:pos] + chr(ord('d') + pstate) + s[pos+1:]
        pos+=1
    if state == "reloadL":
        if s[pos] == " ":
            state = "reloadR"
            pos+=1
        else:
            pos-=1
    if state == "reloadR":
        if s[pos] == " ":
            state = "end"
        else:
            s = s[:pos] + chr(ord(s[pos]) - 3) + s[pos+1:]
            pos+=1
print(s)
        
