LEFT, RIGHT, NO_MOVE = -1, 1, 0

alphabet = {
    'q1': {'a': ['a', RIGHT, 'q1_a'], 'b': ['b', RIGHT, 'q2'], 'c': ['c', RIGHT, 'q1_a'], ' ': [' ', RIGHT, 'q1']},
    'q1_a': {'a': ['a', RIGHT, 'q1_a'], 'b': ['b', RIGHT, 'q2'], 'c': ['c', RIGHT, 'q1_a'], ' ': ['', LEFT, 'q6']},
    'q2': {'a': ['', RIGHT, 'q3'], 'b': ['', RIGHT, 'q3'], 'c': ['', RIGHT, 'q3'], ' ': ['', LEFT, 'q4']},
    'q3': {'a': ['', RIGHT, 'q5'], 'b': ['', RIGHT, 'q5'], 'c': ['', RIGHT, 'q5'], ' ': ['', NO_MOVE, 'qT']},
    'q4': {'a': ['', NO_MOVE, 'qT'], 'b': ['', NO_MOVE, 'qT'], 'c': ['', NO_MOVE, 'qT']},
    'q5': {'a': ['a', RIGHT, 'q5'], 'b': ['b', RIGHT, 'q5'], 'c': ['c', RIGHT, 'q5'], ' ': ['', RIGHT, 'qT']},
    'q6': {'a': ['a', LEFT, 'q6'], 'b': ['b', LEFT, 'q6'], 'c': ['c', LEFT, 'q6'], ' ': ['', RIGHT, 'q4']},
}

current_state = 'q1'
cursor_position = 0
tape = list(' ' + input() + ' ')

while current_state != 'qT':
    symbol, move, next_state = alphabet[current_state][tape[cursor_position]]
    tape[cursor_position], cursor_position, current_state = symbol, cursor_position + move, next_state

print(''.join(tape))
