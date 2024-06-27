table = {'q1': {'a': ['a', 1, 'q2'], 'b': ['b', 1, 'q3'], 'c': ['c', 1, 'q2'], ' ': [' ', 1, 'q1']},
    'q2': {'a': ['a', 1, 'q2'], 'b': ['b', 1, 'q3'], 'c': ['c', 1, 'q2'], ' ': [' ', -1, 'q4']},
    'q3': {'a': ['', 1, 'q5'], 'b': ['', 1, 'q5'], 'c': ['', 1, 'q5'], ' ': [' ', -1, 'q5']},
    'q4': {'a': ['a', -1, 'q4'],  'c': ['c', -1, 'q4'], ' ': [' ', 1, 'q5']},
    'q5': {'a': ['', 0, 'q0'], 'b': ['', 0, 'q0'], 'c': ['', 0, 'q0'],  ' ': [' ', 0, 'q0']},}
memory = list(input())
state = 'q1'
index = 0
while state != 'q0':
    new_value, shift, new_state = table[state][memory[index]]
    memory[index] = new_value
    index += shift
    state = new_state
print(''.join(memory))