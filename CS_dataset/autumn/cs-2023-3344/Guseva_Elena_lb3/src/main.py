L, R, N = -1, 1, 0
tape = list(input())
current_state = 'q1'
head_position = 0

asd={
    'q1':{
        ' ': [' ', R, 'q1'],
        'a': ['a', N, 'qsearch'],
        'b': ['b', R, 'qdel1'],
        'c': ['c', N, 'qsearch']
    },
    'qsearch': {
        ' ': [' ', L, 'qfirst'],
        'a': ['a', R, 'qsearch'],
        'b': ['b', R, 'qdel1'],
        'c': ['c', R, 'qsearch']
    },
    'qfirst':{
        ' ': [' ', R, 'qdel2'],
        'a': ['a', L, 'qfirst'],
        'c': ['c', L, 'qfirst']
    },
    'qdel1': {
        ' ': [' ', L, 'qdel2'],
        'a': ['', R, 'qdel2'],
        'b': ['', R, 'qdel2'],
        'c': ['', R, 'qdel2']
    },
    'qdel2':{
        'a': ['', N, 'qt'],
        'b': ['', N, 'qt'],
        'c': ['', N, 'qt'],
        ' ': [' ', N, 'qt']
    }
}
while current_state != 'qt':
    symbol, move_direction, next_state = asd[current_state][tape[head_position]]
    tape[head_position] = symbol
    head_position+=move_direction
    current_state=next_state

print(*tape, sep='')

