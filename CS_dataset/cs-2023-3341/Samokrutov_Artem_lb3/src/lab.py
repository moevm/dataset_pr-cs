R = +1
L = -1
N = 0

CHANGE_TO = 0
MOVE_TO = 1
NEXT_STATE = 2

def turing_machine(program, tape, start_state, current_cell, end_state):
    current_state = start_state
    
    while True:
        rows = program[current_state]
        current_row = rows[tape[current_cell]]
        tape[current_cell] = current_row[CHANGE_TO]
        if not current_row[MOVE_TO]:
            break
        current_cell += current_row[MOVE_TO] 
        current_state = current_row[NEXT_STATE]

    return ''.join(tape)

program = {'start': {'a': ('a', R, 'skip through'), 'b': ('b', R, 'skip through'), 'c': ('c', R, 'skip through'), ' ': (' ', R, 'start')},
           'skip through': {'a': ('a', R, 'skip through'), 'b': ('b', R, 'skip through'), 'c': ('c', R, 'skip through'), ' ': (' ', L, 'step back')},
           'step back': {'a': ('a', L, 'found first a'), 'b': ('b', L, 'step back'), 'c': ('c', L, 'step back')},
           'found first a': {'a': ('a', L, 'found second a'), 'b': ('b', L, 'step back'), 'c': ('c', L, 'step back')},
           'found second a': {'a': ('a', R, 'read an a'), 'b': ('b', R, 'read a b'), 'c': ('c', R, 'read a c')},
           'read an a': {'a': ('a', R, 'read an a, skip')},
           'read an a, skip': {'a': ('a', R, 'replace with a')},
           'replace with a': {'a': ('a', N, 'end'), 'b': ('a', N, 'end'), 'c': ('a', N, 'end'), ' ': ('a', N, 'end')},
           'read a b': {'a': ('a', R, 'read a b, skip')},
           'read a b, skip': {'a': ('a', R, 'replace with b')},
           'replace with b': {'a': ('b', N, 'end'), 'b': ('b', N, 'end'), 'c': ('b', N, 'end'), ' ': ('b', N, 'end')},
           'read a c': {'a': ('a', R, 'read a c, skip')},
           'read a c, skip': {'a': ('a', R, 'replace with c')},
           'replace with c': {'a': ('c', N, 'end'), 'b': ('c', N, 'end'), 'c': ('c', N, 'end'), ' ': ('c', N, 'end')}}

tape = list(str(input()) + ' ')

print(turing_machine(program, tape, 'start', 0, 'end')[:-1])
