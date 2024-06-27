str = list(input())
st_ar = []
status = "q0"
st_ar.append(status)
i = 0
while (status != "q7"):
    if status == "q0":
        if str[i] == "b":
            status = "q1"
            st_ar.append(status)
            continue
        if str[i] in "a":
            status = "q1"
            i +=1
            st_ar.append(status)
            continue
        if str[i] == "c":
            status = "q1"
            i +=1
            st_ar.append(status)
            continue
        if str[i] == " ":
            i +=1
            st_ar.append(status)
            continue
    if status == "q1":
        if str[i] == "b":
            status = "q2"
            i +=1
            st_ar.append(status)
            continue
        if str[i] == "a":
            i +=1
            st_ar.append(status)
            continue
        if str[i] == "c":
            i +=1
            st_ar.append(status)
            continue
        if str[i] == " ":
            status = "q6"
            i -=1
            st_ar.append(status)
            continue
    if status == "q2":
        if str[i] == "a":
            status = "q3"
            i +=1
            st_ar.append(status)
            continue
        if str[i] == "b":
            status = "q3"
            i +=1
            st_ar.append(status)
            continue
        if str[i] == "c":
            status = "q3"
            i +=1
            st_ar.append(status)
            continue
        if str[i] == " ":
            status = "q5"
            i -=1
            st_ar.append(status)
            continue
    if status == "q3":
        if str[i] == "a":
            str[i] = ""
            status = "q4"
            i -=1
            st_ar.append(status)
            continue
        if str[i] == "b":
            str[i] = ""
            status = "q4"
            i -=1
            st_ar.append(status)
            continue
        if str[i] == "c":
            str[i] = ""
            status = "q4"
            i -=1
            st_ar.append(status)
            continue
        if str[i] == " ":
            status = "q4"
            i -=1
            st_ar.append(status)
            continue
    if status == "q4":
        if str[i] == "a":
            str[i] = ""
            status = "q7"
            st_ar.append(status)
            continue
        if str[i] == "b":
            str[i] = ""
            status = "q7"
            st_ar.append(status)
            continue
        if str[i] == "c":
            str[i] = ""
            status = "q7"
            st_ar.append(status)
            continue
    if status == "q5":
        if str[i] == "b":
            str[i] = ""
            status = "q7"
            st_ar.append(status)
            continue
        if str[i] == "c":
            str[i] = ""
            status = "q7"
            st_ar.append(status)
            continue
    if status == "q6":
        if str[i] == "a":
            i -=1
            st_ar.append(status)
            continue
        if str[i] == "c":
            i -=1
            st_ar.append(status)
            continue
        if str[i] == " ":
            status = "q4"
            i +=1
            st_ar.append(status)
            continue
print(''.join(str))
