START = 'findstart'
END = 'stop'
PROGRAM = {
    'findstart': {
        'a': ('a', 1, 'findend'),
        'b': ('b', 1, 'findend'),
        'c': ('c', 1, 'findend'),
        ' ': (' ', 1, 'findstart'),
    },
    'findend': {
        'a': ('a', 1, 'findend'),
        'b': ('b', 1, 'findend'),
        'c': ('c', 1, 'findend'),
        ' ': (' ', -1, 'returntoa'),
    },
    'returntoa': {
        'a': ('a', -1, 'checkfora'),
        'b': ('b', -1, 'returntoa'),
        'c': ('c', -1, 'returntoa'),
    },
    'checkfora': {
        'a': ('a', -1, 'readsymbol'),
        'b': ('b', -1, 'returntoa'),
        'c': ('c', -1, 'returntoa'),
    },
    'readsymbol': {
        'a': ('a', 1, 'pullatwo'),
        'b': ('b', 1, 'pullbtwo'),
        'c': ('c', 1, 'pullctwo'),
    },
    'pullatwo': {
        'a': ('a', 1, 'pullaone'),
    },
    'pullbtwo': {
        'a': ('a', 1, 'pullbone'),
    },
    'pullctwo': {
        'a': ('a', 1, 'pullcone'),
    },
    'pullaone': {
        'a': ('a', 1, 'placea'),
    },
    'pullbone': {
        'a': ('a', 1, 'placeb'),
    },
    'pullcone': {
        'a': ('a', 1, 'placec'),
    },
    'placea': {
        'a': ('a', 0, 'stop'),
        'b': ('a', 0, 'stop'),
        'c': ('a', 0, 'stop'),
        ' ': ('a', 0, 'stop'),
    },
    'placeb': {
        'a': ('b', 0, 'stop'),
        'b': ('b', 0, 'stop'),
        'c': ('b', 0, 'stop'),
        ' ': ('b', 0, 'stop'),
    },
    'placec': {
        'a': ('c', 0, 'stop'),
        'b': ('c', 0, 'stop'),
        'c': ('c', 0, 'stop'),
        ' ': ('c', 0, 'stop'),
    },
}


mem = list(' ' + input() + ' ')
c = 0
state = START
history = [START]

for i in range(10**10):
    write, move, nstate = PROGRAM[state][mem[c]]
    mem[c] = write
    c += move
    history.append(nstate)
    if nstate == END:
        break
    state = nstate

print(''.join(mem[1:-1]))
#print(' '.join(history)) # Показывает историю изменения состояний
