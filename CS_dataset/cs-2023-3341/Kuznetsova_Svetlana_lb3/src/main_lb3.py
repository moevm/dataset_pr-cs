R = +1
L = -1
N = 0

CHANGE_TO = 0
MOVE_TO = 1
NEXT_STATE = 2

def turing_machine(program, tape, start_state, current_cell):
    current_state = start_state
    
    rows = program[current_state]
    current_row = rows[tape[current_cell]]
    tape[current_cell] = current_row[CHANGE_TO]
    while (current_row[MOVE_TO]):
        current_cell += current_row[MOVE_TO] 
        current_state = current_row[NEXT_STATE]
        rows = program[current_state]
        current_row = rows[tape[current_cell]]
        tape[current_cell] = current_row[CHANGE_TO]


    return ''.join(tape)

program = {'q_start': {'a': ('a', L, 'q_found'), 'b': ('b', L, 'q_found'), 'c': ('c', L, 'q_found'), ' ': (' ', R, 'q_start')},
         'q_found': {'a': ('a', L, 'q_found'), 'b': ('b', L, 'q_found'), 'c': ('c', L, 'q_found'), ' ': (' ', R, 'q_back')},
         'q_back': {'a': ('0', L, 'q_a'), 'b': ('0', L, 'q_b'), 'c': ('0', L, 'q_c'), 'A': ('A', R, 'q_back'), 'B': ('B', R, 'q_back'), 'C': ('C', R, 'q_back'), '0': ('0', R, 'q_back'), ' ': (' ', L, 'q_end'),},
         'q_a': {'A': ('A', L, 'q_a'), 'B': ('B', L, 'q_a'), 'C': ('C', L, 'q_a'), '0': ('0', L, 'q_a'), ' ': ('A', R, 'q_back')},
         'q_b': {'A': ('A', L, 'q_b'), 'B': ('B', L, 'q_b'), 'C': ('C', L, 'q_b'), '0': ('0', L, 'q_b'), ' ': ('B', R, 'q_back')},
         'q_c': {'A': ('A', L, 'q_c'), 'B': ('B', L, 'q_c'), 'C': ('C', L, 'q_c'), '0': ('0', L, 'q_c'), ' ': ('C', R, 'q_back')},
         'q_end': {'0': (' ', L, 'q_end'), 'A': ('a', L, 'q_end'), 'B': ('b', L, 'q_end'), 'C': ('c', L, 'q_end'), ' ': (' ', N, 'q_stop')}}

tape = list(15*' '+str(input())+' ')
index = 0
state = 'q_start'

print(turing_machine(program, tape, state, index).replace(' ',''))
