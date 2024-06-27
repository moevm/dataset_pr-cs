q_table ={
'q1':{' ': " Rq1",'a': "aRq2",'c': "cRq2",'b': "bRq3"},
'q2':{' ': " Lq4",'a': "aRq2",'c': "cRq2",'b': "bRq3"},
'q3':{' ': " Lq4",'a': " Rq6",'c': " Rq6",'b': " Rq6"},
'q4':{' ': " Rq5",'a': "aLq4",'c': "cLq4",'b': " Nq16"},
'q5':{'a': " Nq16",'c': " Nq16"},
'q6':{' ': " Nq16",'a': " Rq7",'c': " Rq7",'b': " Rq7"},
'q7':{' ': " Nq16",'a': " Lq8",'c': " Lq11",'b': " Lq13"},
'q8':{' ': " Lq9"},
'q9':{' ': "aRq10"},
'q10':{' ': " Rq15"},
'q11':{' ': " Lq12"},
'q12':{' ': "cRq10"},
'q13':{' ': " Lq14"},
'q14':{' ': "bRq10"},
'q15':{' ': " Rq7"}
}

direction = {'R' : 1, 'L' : -1, 'N' : 0}

tape = list(input())
state = "q1"
cell_number = 0
symbol = tape[cell_number]

while(state != "q16"):
    symbol = tape[cell_number]
    tape[cell_number] = q_table[state][symbol][0:1]
    cell_number += direction[q_table[state][symbol][1:2]]
    state = q_table[state][symbol][2:]

print(''.join(tape))
