def q0(cell):
    if cell == ' ':
        return ' ', 1, 'q0'
    return cell, 0, 'q1'


def q1(cell):
    if cell == ' ':
        return 'a', -1, 'q2'
    return cell, 1, 'q1'


def q2(cell):
    if cell == 'a':
        return ' ', -1, 'q3'
    if cell == 'b':
        return ' ', 1, 'q8'
    if cell == 'c':
        return ' ', 1, 'q10'


def q3(cell):
    if cell == ' ':
        return ' ', 1, 'q4'
    return cell, 1, 'q6'


def q4(cell):
    if cell == ' ':
        return ' ', 1, 'q4'
    return ' ', 1, 'q5'


def q5(cell):
    if cell == ' ':
        return 'a', 0, 'qT'
    return cell, 1, 'q5'


def q6(cell):
    if cell == ' ':
        return ' ', 1, 'q6'
    return cell, 0, 'q7'


def q7(cell):
    if cell == ' ':
        return 'a', -1, 'q12'
    return cell, 1, 'q7'


def q8(cell):
    if cell == ' ':
        return ' ', 1, 'q8'
    return cell, 0, 'q9'


def q9(cell):
    if cell == ' ':
        return 'b', -1, 'q12'
    return cell, 1, 'q9'


def q10(cell):
    if cell == ' ':
        return ' ', 1, 'q10'
    return cell, 0, 'q11'


def q11(cell):
    if cell == ' ':
        return 'c', -1, 'q12'
    return cell, 1, 'q11'


def q12(cell):
    if cell == ' ':
        return ' ', -1, 'q13'
    return cell, -1, 'q12'


def q13(cell):
    if cell == ' ':
        return ' ', -1, 'q13'
    return cell, 0, 'q2'


tape = ' ' * 40 + input() + ' ' * 40
tape = list(tape)
state = 'q0'
index = 0
state_dict = {'q0': q0, 'q1': q1, 'q2': q2, 'q3': q3, 'q4': q4, 'q5': q5, 'q6': q6, 'q7': q7, 'q8': q8, 'q9': q9,
              'q10': q10, 'q11': q11, 'q12': q12, 'q13': q13}
while (state != 'qT'):
    new_symbol, shift, state = state_dict[state](tape[index])
    tape[index] = new_symbol
    index += shift
answer = ''.join(tape)
print(answer)

