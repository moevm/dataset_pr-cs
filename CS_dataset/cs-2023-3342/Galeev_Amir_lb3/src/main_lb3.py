def turing_machine(input_tape):
    input_tape = ' ' + input_tape
    tape = list(input_tape)
    state = 'q0'
    head_position = 0
    states_history = [state]
    transitions = {
        ('q0', 'a'): ('a', 'R', 'q1'),   ('q1', 'a'): ('a', 'L', 'q2'),   ('q2', 'a'): ('a', 'L', 'q2'),   ('q3', 'a'): ('a', 'R', 'q3'),   ('q4', 'a'): ('a', 'N', 'q14'),
        ('q0', 'b'): ('b', 'R', 'q0'),   ('q1', 'b'): ('b', 'L', 'q5'),   ('q2', 'b'): ('b', 'L', 'q2'),   ('q3', 'b'): ('b', 'R', 'q3'),   ('q4', 'b'): ('a', 'N', 'q14'),
        ('q0', 'c'): ('c', 'R', 'q0'),   ('q1', 'c'): ('c', 'L', 'q8'),   ('q2', 'c'): ('c', 'L', 'q2'),   ('q3', 'c'): ('c', 'L', 'q4'),   ('q4', 'c'): ('a', 'N', 'q14'),
        ('q0', ' '): (' ', 'R', 'q0'),   ('q1', ' '): (' ', 'L', 'q11'),   ('q2', ' '): (' ', 'R', 'q3'),   ('q3', ' '): (' ', 'R', 'q3'),   ('q4', ' '): ('a', 'N', 'q14'),

                                                                          ('q5', 'a'): ('a', 'L', 'q5'),   ('q6', 'a'): ('a', 'R', 'q6'),   ('q7', 'a'): ('b', 'N', 'q14'),
                                                                          ('q5', 'b'): ('b', 'L', 'q5'),   ('q6', 'b'): ('b', 'R', 'q6'),   ('q7', 'b'): ('b', 'N', 'q14'),
                                                                          ('q5', 'c'): ('c', 'L', 'q5'),   ('q6', 'c'): ('c', 'L', 'q7'),   ('q7', 'c'): ('b', 'N', 'q14'),
                                                                          ('q5', ' '): (' ', 'R', 'q6'),   ('q6', ' '): (' ', 'R', 'q6'),   ('q7', ' '): ('b', 'N', 'q14'),

                                                                          ('q8', 'a'): ('a', 'L', 'q8'),   ('q9', 'a'): ('a', 'R', 'q9'),   ('q10', 'a'): ('c', 'N', 'q14'),
                                                                          ('q8', 'b'): ('b', 'L', 'q8'),   ('q9', 'b'): ('b', 'R', 'q9'),   ('q10', 'b'): ('c', 'N', 'q14'),
                                                                          ('q8', 'c'): ('c', 'L', 'q8'),   ('q9', 'c'): ('c', 'L', 'q10'),   ('q10', 'c'): ('c', 'N', 'q14'),
                                                                          ('q8', ' '): (' ', 'R', 'q9'),   ('q9', ' '): (' ', 'R', 'q9'),   ('q10', ' '): ('c', 'N', 'q14'),

                                                                          ('q11', 'a'): ('a', 'L', 'q11'),   ('q12', 'a'): ('a', 'R', 'q12'),   ('q13', 'a'): ('a', 'N', 'q14'),
                                                                          ('q11', 'b'): ('b', 'L', 'q11'),   ('q12', 'b'): ('b', 'R', 'q12'),   ('q13', 'b'): ('a', 'N', 'q14'),
                                                                          ('q11', 'c'): ('c', 'L', 'q11'),   ('q12', 'c'): ('c', 'L', 'q13'),   ('q13', 'c'): ('a', 'N', 'q14'),
                                                                          ('q11', ' '): (' ', 'R', 'q12'),   ('q12', ' '): (' ', 'R', 'q12'),   ('q13', ' '): ('a', 'N', 'q14'),
    }
    while state != 'q14':
        symbol = tape[head_position]
        new_symbol, move, new_state = transitions.get((state, symbol), (' ', 'N', 'q14'))
        tape[head_position] = new_symbol
        if move == 'R' and head_position < len(tape) - 1:
            head_position += 1
        elif move == 'L' and head_position > 0:
            head_position -= 1
        state = new_state
        states_history.append(state)
    result_tape = ''.join(tape)

    return result_tape

input_tape = input()
result_tape = turing_machine(input_tape)
print(result_tape)