"""
Вид ф-ции для состояния
def qN(cell): #cell - текущая ячейка на ленте
    ....
    #V - значение записываемое в текущую ячейку 
    #S - Сдвиг R N L (1 0 -1)
    #new_q - состояние в которое перейдет автомат после операции
    return V, S, new_q
"""
space = ' '


def q1(cell):
    if cell != space: return cell, 0, 2
    return cell, 1, 1


def q2(cell):
    if cell == space: return cell, -1, 3
    if cell == 'b': return cell, 1, 5
    return cell, 1, 2


def q3(cell):
    if cell == space: return cell, 1, 4
    return cell, -1, 3


def q4(cell):
    return space, 0, 8


def q5(cell):
    if cell == space: return cell, -1, 4
    return cell, 1, 6


def q6(cell):
    if cell == space: return cell, -1, 4
    return '', -1, 7


def q7(cell):
    return '', 0, 8


def q8(cell):
    return cell, 0, 8


q_dict = {
    1: q1,
    2: q2,
    3: q3,
    4: q4,
    5: q5,
    6: q6,
    7: q7,
    8: q8
}


belt = list(input())
i = 0
condition = 1

while condition != 8:
    answer = q_dict[condition](belt[i])
    belt[i] = answer[0]
    i += answer[1]
    condition = answer[2]


print(''.join(belt))
