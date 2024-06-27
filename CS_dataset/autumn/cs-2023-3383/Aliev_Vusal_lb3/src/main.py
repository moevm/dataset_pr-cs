memory = list(input())
index = 0
state = 'q1'

table = {
    'q1':{
        'a':('a', 1, 'q2'),
        'b':('b', 1, 'q2'),
        'c':('c', 1, 'q2'), #находим первый символ строки
        ' ':(' ', 1,'q1')
    },
    'q2':{
        'a':('a', 1, 'q2'),
        'b':('b', 1, 'q2'),
        'c':('c', 1, 'q2'), #проходим всю строку и останавливайся на последнем символе
        ' ':(' ', -1, 'q3'),
    },
    'q3':{
        'a':('a', -1, 'q4'),
        'b':('b', -1, 'q3'), #поиск первого 'a'
        'c':('c', -1, 'q3'),
    },
    'q4':{
        'a':('a', -1, 'q5'),
        'b':('b', -1, 'q3'), #поиск второго 'a', в итоге два подряд идущих 'aa'
        'c':('c', -1, 'q3'),
    },
    'q5':{
        'a':('a', 1, 'qa'),
        'b':('b', 1, 'qb'), #поиск символа, который стоит перед 'aa'
        'c':('c', 1, 'qc'),
    },
    'qa':{
        'a':('a', 1, 'qa'),
        'b':('a', 0, 'qT'), #qa если перед 'aa' стоит символ 'a'
        'c':('a', 0, 'qT'), #заменяем 'b', 'c' на 'а'
        ' ':('a', 0, 'qT')
    },
    'qb':{
        'a':('a', 1, 'qb'),
        'b':('b', 0, 'qT'), #qb если перед 'aa' стоит 'b'
        'c':('b', 0, 'qT'), #заменяем элементы на 'b'
        ' ':('b', 0, 'qT')
    },
    'qc':{
        'a':('a', 1, 'qc'),
        'b':('c', 0, 'qT'),
        'c':('c', 0, 'qT'), #аналогично
        ' ':('c', 0, 'qT'),
    }
}   

while state != 'qT':
    symbol = memory[index]
    new_symbol, delta, state = table[state][symbol]
    memory[index] = new_symbol
    index += delta

print(''.join(memory))