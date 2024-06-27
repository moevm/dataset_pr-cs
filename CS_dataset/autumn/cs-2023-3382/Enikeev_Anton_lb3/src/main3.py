L, N, R = -1, 0, 1

letters = {
    'a': 0, 'b': 1, 'c': 2, ' ': 3,
}

#словарь состояний
states = {
    'q0': {
        'write': ['a', ' ', ' ', ' '],
        'move': [R, R, R, R],
        'next': ['q1', 'q2', 'q3', 'q0'],
    },
    'q1': {
        'write': ['a', 'b', 'c', ' '],
        'move': [R, R, R, R],
        'next': ['q1', 'q2', 'q3', 'q7'],
    },
    'q2': {
        'write': ['a', 'b', 'c', ' '],
        'move': [R, R, R, R],
        'next': ['q1', 'q2', 'q3', 'q8'],
    },
    'q3': {
        'write': ['a', 'b', 'c', ' '],
        'move': [R, R, R, R],
        'next': ['q1', 'q2', 'q3', 'q9'],
    },
    'q4': {
        'write': ['a', 'b', 'c', ' '],
        'move': [L, L, L, L],
        'next': ['q4', 'q4', 'q4', 'q5'],
    },
    'q5': {
        'write': [' ', ' ', ' ', ' '],
        'move': [L, L, L, L],
        'next': ['q6', 'q6', 'q6', 'q5'],
    },
    'q6': {
        'write': ['a', 'b', 'c', ' '],
        'move': [R, R, R, N],
        'next': ['q10', 'q11', 'q12', 'q13'],
    },
    'q7': {
        'write': ['a', 'b', 'c', 'a'],
        'move': [R, R, R, L],
        'next': ['q7', 'q7', 'q7', 'q4'],
    },
    'q8': {
        'write': ['a', 'b', 'c', 'b'],
        'move': [R, R, R, L],
        'next': ['q8', 'q8', 'q8', 'q4'],
    },
    'q9': {
        'write': ['a', 'b', 'c', 'c'],
        'move': [R, R, R, L],
        'next': ['q9', 'q9', 'q9', 'q4'],
    },
    'q10': {
        'write': ['a', 'b', 'c', ' '],
        'move': [R, R, R, R],
        'next': ['q7', 'q7', 'q7', 'q10'],
    },
    'q11': {
        'write': ['a', 'b', 'c', ' '],
        'move': [R, R, R, R],
        'next': ['q8', 'q8', 'q8', 'q11'],
    },
    'q12': {
        'write': ['a', 'b', 'c', ' '],
        'move': [R, R, R, R],
        'next': ['q9', 'q9', 'q9', 'q12'],
    },
} 
tape = list(input())
tape += ((len(tape) + 2) * ' ')

state = 'q0'
#позиция в ленте
index = 0
while state != 'q13':
    old_value = tape[index]
    tape[index] = states[state]['write'][letters[old_value]]
    index += states[state]['move'][letters[old_value]]
    state = states[state]['next'][letters[old_value]]

print(''.join(tape))
