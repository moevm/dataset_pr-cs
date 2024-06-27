L,N,R=-1,0,1
table = {
    "q1": {'a':['a',R,"q2"],'b':['b',R,"q2"],'c':['c',R,"q2"],' ':[' ',R,"q1"]},
    "q2": {'a':['a',R,"q2"],'b':['b',R,"q2"],'c':['c',R,"q2"],' ':[' ',L,"q3"]},
    "q3": {'a':['d',R,"q4"],'b':['d',R,"q5"],'c':['d',R,"q6"],'d':['d',L,"q3"],' ':[' ',R,"q8"]},
    "q4": {'a':['a',R,"q4"],'b':['b',R,"q4"],'c':['c',R,"q4"],'d':['d',R,"q4"],' ':['a',L,"q7"]},
    "q5": {'a':['a',R,"q5"],'b':['b',R,"q5"],'c':['c',R,"q5"],'d':['d',R,"q5"],' ':['b',L,"q7"]},
    "q6": {'a':['a',R,"q6"],'b':['b',R,"q6"],'c':['c',R,"q6"],'d':['d',R,"q6"],' ':['c',L,"q7"]},
    "q7": {'a':['a',L,"q7"],'b':['b',L,"q7"],'c':['c',L,"q7"],'d':['d',L,"q3"]},
    "q8": {'a':['a',N,"q9"],'b':['b',N,"q9"],'c':['c',N,"q9"],'d':[' ',R,"q8"]}
}

mem = list(" " + input() + "              ") 
state = "q1"
ind = 0
while state != "q9":
    symbol = mem[ind]
    next_s = table[state][symbol]
    mem[ind] = next_s[0]
    ind += next_s[1]
    state = next_s[2]
print("".join(mem))
