alf = ' #abc'
tape = dict(enumerate(input()))

def current():
	simbol = tape.get(index,' ')
	tape.update({index: simbol})
	return simbol

def upd(d1, d2):
	d = d1.copy()
	d.update(d2)
	return d

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

"""
#Таблица в явном виде:

def show_table():
	print('table = {')
	for k in list(table.keys()):
		print('\t'+f"'{k}': {table[k]}")
	print('}')

table = {
	'start': {' ': [' ', 1, 'start'], '#': ['#', 1, 'start'], 'a': ['a', 1, 'get'], 'b': ['b', 1, 'start'], 'c': ['c', 1, 'start']}
	'get': {'#': ['#', 1, 'get'], ' ': [' ', -1, 'clean'], 'a': ['#', -1, 'put_a'], 'b': ['#', -1, 'put_b'], 'c': ['#', -1, 'put_c']}
	'put_a': {' ': ['a', 1, 'find_#'], '#': ['#', -1, 'put_a'], 'a': ['a', -1, 'put_a'], 'b': ['b', -1, 'put_a'], 'c': ['c', -1, 'put_a']}
	'put_b': {' ': ['b', 1, 'find_#'], '#': ['#', -1, 'put_b'], 'a': ['a', -1, 'put_b'], 'b': ['b', -1, 'put_b'], 'c': ['c', -1, 'put_b']}
	'put_c': {' ': ['c', 1, 'find_#'], '#': ['#', -1, 'put_c'], 'a': ['a', -1, 'put_c'], 'b': ['b', -1, 'put_c'], 'c': ['c', -1, 'put_c']}
	'find_#': {' ': [' ', 1, 'find_#'], '#': ['#', 1, 'get'], 'a': ['a', 1, 'find_#'], 'b': ['b', 1, 'find_#'], 'c': ['c', 1, 'find_#']}
	'clean': {'#': [' ', -1, 'clean'], 'a': ['a', 0, 'end']}
	'end': {}
}

show_table()
"""

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
