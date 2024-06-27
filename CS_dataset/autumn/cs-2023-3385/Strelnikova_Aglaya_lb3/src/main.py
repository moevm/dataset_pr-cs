table = {
        'q0' : { 'a': ['a', 1, 'q1'], 'b' : ['b', 1, 'q0'], 'c' : ['c', 1, 'q0'], ' ': [ ' ', 1, 'q0'] },

        'q1' : { 'a': ['a', -1, 'q1a'], 'b' : ['b', -1, 'q1b'], 'c' : ['c', -1, 'q1c'], ' ': [ ' ', -1, 'q1a'] },

        'q1a' : { 'a': ['a', -1, 'q1a'], 'b' : ['b', -1, 'q1a'], 'c' : ['c', -1, 'q1a'], ' ': [ ' ', 1, 'q2a'] },
        'q2a' : { 'a': ['a', 1, 'q2a'], 'b' : ['b', 1, 'q2a'], 'c' : ['c', -1, 'q3a']},
        'q3a' : { 'a': ['a', 0, 'qQ'], 'b' : ['a', 0, 'qQ'], ' ': [ 'a', 0, 'qQ'] },

        'q1b': {'a': ['a', -1, 'q1b'], 'b': ['b', -1, 'q1b'], 'c': ['c', -1, 'q1b'], ' ': [' ', 1, 'q2b']},
        'q2b': {'a': ['a', 1, 'q2b'], 'b': ['b', 1, 'q2b'], 'c': ['c', -1, 'q3b']},
        'q3b': {'a': ['b', 0, 'qQ'], 'b': ['b', 0, 'qQ'], ' ': ['b', 0, 'qQ']},

        'q1c' : { 'a': ['a', -1, 'q1c'], 'b' : ['b', -1, 'q1c'], 'c' : ['c', -1, 'q1c'], ' ': [ ' ', 1, 'q2c'] },
        'q2c': {'a': ['a', 1, 'q2c'], 'b': ['b', 1, 'q2c'], 'c': ['c', -1, 'q3c']},
        'q3c': {'a': ['c', 0, 'qQ'], 'b': ['c', 0, 'qQ'], ' ': ['a', 0, 'qQ']}

}
mem = list(input())
q = 'q0'
i = 0

while q != 'qQ':
    s, mov,st = table[q][mem[i]]
    mem[i] = s
    i += mov
    q=st

print(''.join(mem))