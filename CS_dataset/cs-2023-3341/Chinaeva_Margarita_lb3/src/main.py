R= +1
L= -1
N = 0

CHANGE_TO = 0
MOVE_TO = 1
NEXT_Q = 2

program = {
	'q1' : {'a' : ['a', R, 'q2'], 'b' : ['b', R, 'q2'], 'c' : ['c', R, 'q2'], ' ' : [' ', R, 'q1']},
	'q2' : {'a' : ['a', R, 'q2'], 'b' : ['b', R, 'q2'], 'c' : ['c', R, 'q2'], ' ' : [' ', L, 'q3']},
 	'q3' : {'a' : ['a', L, 'q4'], 'b' : ['b', L, 'q3'], 'c' : ['c', L, 'q3']},
  	'q4' : {'a' : ['a', L, 'q5'], 'b' : ['b', L, 'q3'], 'c' : ['c', L, 'q3']},
   	'q5' : {'a' : ['a', R, 'q6'], 'b' : ['b', R, 'q7'], 'c' : ['c', R, 'q8']},
    'q6' : {'a' : ['a', R, 'q6'], 'b' : ['a', N, 'q9'], 'c' : ['a', N, 'q9'], ' ' : ['a', N, 'q9']},
    'q7' : {'a' : ['a', R, 'q7'], 'b' : ['b', N, 'q9'], 'c' : ['b', N, 'q9'], ' ' : ['b', N, 'q9']},
    'q8' : {'a' : ['a', R, 'q8'], 'b' : ['c', N, 'q9'], 'c' : ['c', N, 'q9'], ' ' : ['c', N, 'q9']}
}

def turing_machine(tape, current_state, index):
    check_end=1
    while check_end:
        now=program[current_state][tape[index]]
        if now[NEXT_Q] == 'q9':
            check_end=0
        tape[index]=now[CHANGE_TO]
        index+= now[MOVE_TO]
        current_state = now[NEXT_Q]
    return tape

tape=list(input())
current_state='q1'
index=0
print(''.join(turing_machine(tape, current_state, index)))
