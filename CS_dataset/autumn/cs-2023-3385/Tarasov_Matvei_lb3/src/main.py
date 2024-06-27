alf = ' #abc'
tape = dict(enumerate(input()))
def current():
    simbol = tape.get(index,' ')
    tape.update({index: simbol})
    return simbol
def upd(q1, q2):
    q = q1.copy()
    q.update(q2)
    return q
L, N, R = [-1,0,1]
move_rigth = lambda state: {a:[a, R, state] for a in alf}
move_left = lambda state: {a:[a, L, state] for a in alf}
table = {
    'start': upd(move_rigth('start'), {'a': ['a', R,'get']}),
    'get': upd({'#':['#',R,'get'], ' ':[' ', L, 'clean']}, {x:['#', L, f'put_{x}'] for x in alf[2:]}), 
    **{f'put_{x}': upd(move_left(f'put_{x}'), {' ': [x, R, 'find_#']}) for x in alf[2:]},
    'find_#': upd(move_rigth('find_#'), {'#': ['#', R, 'get']}),
    'clean': {'#':[' ', L, 'clean'], 'a':['a', N, 'end']},
    'end': {},
}

def show():
    for k in sorted(list(tape.keys())):
        print(tape[k], end='')
    print('',end='\n')
index = 0
state = 'start'
while state != 'end':
    tape[index], delta, state = table[state][current()]
    index += delta
show()