space = ' '


def q0(element):   
    if element != space:
        return element, 0, 1
    if element == space:
        return element, 1, 0


def q1(element):
    if element == 'b':
        return element, 1, 3
    if element == 'a' or element == 'c':
        return element, 1, 1
    if element == space:
        return element, - 1, 2


def q2(element):
    if element != space:
        return element, -1, 2
    if element == space:
        return element, 1, 6


def q3(element):
    if element == space:
        return element, -1, 4
    if element != space:
        return '', 1, 5


def q4(element):
    return '', 0, 7


def q5(element):
    if element != space:
        return '', 0, 7
    if element == space:
        return element, 0, 7


def q6(element):
    return '', 0, 7


def q7(element):
    pass

        
statements_dict = {
    0: q0,
    1: q1,
    2: q2,
    3: q3,
    4: q4,
    5: q5,
    6: q6,
    7: q7,
}

tape = list(input())
current_state = 0
current_element = 0

while current_state != 7:
    q_result = statements_dict[current_state](tape[current_element])
    tape[current_element] = q_result[0]
    current_element  += q_result[1]
    current_state = q_result[2]

print(''.join(tape))
