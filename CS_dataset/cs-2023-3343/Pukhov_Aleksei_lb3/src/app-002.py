table = {
    'q0': {'a': ('a', 1, 'q1'), 'b': ('b', 1, 'q0'), 'c': ('c', 1, 'q0'), ' ': (' ', 1, 'q0')},
    'q1': {'a': ('a', -1, 'qa'), 'b': ('b', -1, 'qb'), 'c': ('c', -1, 'qc'), ' ': (' ', -1, 'qa')},

    'qa':{'a': ('a', -1, 'qa'), 'b': ('b', -1, 'qa'), 'c': ('c', -1, 'qa'), ' ': (' ', 1, 'qa1')},
    'qa1':{'a': ('a', 1, 'qa1'), 'b': ('b', 1, 'qa1'), 'c': ('c', -1, 'qac')},
    'qac':{'a': ('a', 0, 'qT'), 'b': ('a', 0, 'qT'), ' ':('a',0,'qT')},

    'qb':{'a': ('a', -1, 'qb'), 'b': ('b', -1, 'qb'), 'c': ('c', -1, 'qb'), ' ': (' ', 1, 'qb1')},
    'qb1':{'a': ('a', 1, 'qb1'), 'b': ('b', 1, 'qb1'), 'c': ('c', -1, 'qbc')},
    'qbc':{'a': ('b', 0, 'qT'), 'b': ('b', 0, 'qT'), ' ':('b',0,'qT')},

    'qc': {'a': ('a', -1, 'qc'), 'b': ('b', -1, 'qc'), 'c': ('c', -1, 'qc'), ' ': (' ', 1, 'qc1')},
    'qc1': {'a': ('a', 1, 'qc1'), 'b': ('b', 1, 'qc1'), 'c': ('c', -1, 'qcc')},
    'qcc': {'a': ('c', 0, 'qT'), 'b': ('c', 0, 'qT'), ' ':('c',0,'qT')},
}

memory = input()
memory = list(' ' + memory + ' ')
index = 0
state = 'q0'

while state != 'qT':
    sim = memory[index]
    new_sim, delta, state = table[state][sim]
    memory[index] = new_sim
    index += delta
print(''.join(memory))