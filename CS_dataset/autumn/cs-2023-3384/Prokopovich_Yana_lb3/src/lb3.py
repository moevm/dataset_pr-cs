table = {
    'qa': {'a': ['a', 1, 'qr'], 'b': ['b', 1, 'qa'], 'c': ['c', 1, 'qa'], ' ': [' ', 1, 'qa']},
    'qr': {'a': ['a', -1, 'qma_a'], 'b': ['b', -1, 'qma_b'], 'c': ['c', -1, 'qma_c'], ' ': [' ', -1, 'qma_a']},
    'qma_a': {'a': ['a', -1, 'qma_a'], 'b': ['b', -1, 'qma_a'], 'c': ['c', -1, 'qma_a'], ' ': [' ', 1, 'qfc_a']},
    'qma_b': {'a': ['a', -1, 'qma_b'], 'b': ['b', -1, 'qma_b'], 'c': ['c', -1, 'qma_b'], ' ': [' ', 1, 'qfc_b']},
    'qma_c': {'a': ['a', -1, 'qma_c'], 'b': ['b', -1, 'qma_c'], 'c': ['c', -1, 'qma_c'], ' ': [' ', 1, 'qfc_c']},
    'qfc_a': {'a': ['a', 1, 'qfc_a'], 'b': ['b', 1, 'qfc_a'], 'c': ['c', -1, 'qr_a'], ' ': [' ', 0, 'qT']},
    'qfc_b': {'a': ['a', 1, 'qfc_b'], 'b': ['b', 1, 'qfc_b'], 'c': ['c', -1, 'qr_b'], ' ': [' ', 0, 'qT']},
    'qfc_c': {'a': ['a', 1, 'qfc_c'], 'b': ['b', 1, 'qfc_c'], 'c': ['c', -1, 'qr_c'], ' ': [' ', 0, 'qT']},
    'qr_a': {'a': ['a', 0, 'qT'], 'b': ['a', 0, 'qT'], 'c': ['a', 0, 'qT'], ' ': ['a', 0, 'qT']},
    'qr_b': {'a': ['b', 0, 'qT'], 'b': ['b', 0, 'qT'], 'c': ['b', 0, 'qT'], ' ': ['b', 0, 'qT']},
    'qr_c': {'a': ['c', 0, 'qT'], 'b': ['c', 0, 'qT'], 'c': ['c', 0, 'qT'], ' ': ['c', 0, 'qT']}
}

memory = list(input())
index = 0
new_symbol = ''
state = 'qa'
states = [state]

while state != 'qT':
    new_symbol, delta, state = table[state][memory[index]]
    memory[index] = new_symbol
    index += delta
    states.append(state)

print("".join(memory))