L, R, N = -1, 1, 0
table = {
    'start': {'a': ['a', R, 'str'], 'b': ['b', R, 'str'], 'c': ['c', R, 'str'], ' ': [' ', R, 'start']},
    'str': {'a': ['a', R, 'str'], 'b': ['b', R, 'str'], 'c': ['c', R, 'str'], ' ': [' ', L, 'found']},
    'found': {'a': ['a', L, 'found_a'], 'b': ['b', L, 'found_b'], 'c': ['c', L, 'found_c'], ' ': [' ', N, 'end']},
    'found_a': {'a': ['a', L, 'found_aa'], 'b': ['b', L, 'found_b'], 'c': ['c', L, 'found_c'], ' ': [' ', N, 'end']},
    'found_aa': {'a': ['a', R, 'found_aaa'], 'b': ['b', R, 'found_aab'], 'c': ['c', R, 'found_aac'], ' ': [' ', N, 'end']},
    'found_aaa': {' ': ['a', N, 'end'], 'a': ['a', R, 'found_aaa']},
    'found_aab': {' ': ['b', N, 'end'], 'a': ['a', R, 'found_aab']},
    'found_aac': {' ': ['c', N, 'end'], 'a': ['a', R, 'found_aac']},
    'found_b': {'a': ['a', L, 'found_ba'], 'b': ['b', L, 'found_b'], 'c': ['c', L, 'found_c'], ' ': [' ', N, 'end']},
    'found_ba': {'a': ['a', L, 'found_baa'], 'b': ['b', L, 'found_b'], 'c': ['c', L, 'found_c'], ' ': [' ', N, 'end']},
    'found_baa': {'b': ['b', N, 'end'], 'c': ['c', R, 'found_baac'], 'a': ['a', R, 'found_baaa'], ' ': [' ', N, 'end']},
    'found_baac': {'b': ['c', N, 'end'], 'a': ['a', R, 'found_baac']},
    'found_baaa': {'b': ['a', N, 'end'], 'a': ['a', R, 'found_baaa']},
    'found_c': {'a': ['a', L, 'found_ca'], 'b': ['b', L, 'found_b'], 'c': ['c', L, 'found_c'], ' ': [' ', N, 'end']},
    'found_ca': {'a': ['a', L, 'found_caa'], 'b': ['b', L, 'found_b'], 'c': ['c', L, 'found_c'], ' ': [' ', N, 'end']},
    'found_caa': {'a': ['a', R, 'found_caaa'], 'b': ['b', R, 'found_caab'], 'c': ['c', N, 'end'], ' ': [' ', N, 'end']},
    'found_caab': {'c': ['b', N, 'end'], 'a': ['a', R, 'found_caab']},
    'found_caaa': {'c': ['a', N, 'end'], 'a': ['a', R, 'found_caaa']}
}

memory = list(input())

state = 'start'
ind = 0
states = [state]

while state != 'end':
    symbol, i, state = table[state][memory[ind]]
    memory[ind] = symbol
    ind += i
    states.append(state)

print(*memory, sep='')
