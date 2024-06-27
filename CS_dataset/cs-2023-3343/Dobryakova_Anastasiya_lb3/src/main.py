R, L, N = 1, -1, 0

states = {
    'q1': {'a': ['a', R, 'q2'], 'b': ['b', R, 'q1'], 'c': ['c', R, 'q1'], ' ': [' ', R, 'q1']},
    'q2': {'a': ['a', R, 'q3'], 'b': ['b', R, 'q1'], 'c': ['c', R, 'q1'], ' ': [' ', R, 'q1']},
    'q3': {'a': ['a', L, 'q7'], 'b': ['b', L, 'q4'], 'c': ['c', L, 'q10'], ' ': [' ', L, 'q7']},
    'q7': {'a': ['a', L, 'q8']},
    'q8': {'a': ['a', L, 'q9']},
    'q9': {'a': ['a', R, 'q_out'], 'b': ['a', R, 'q_out'], 'c': ['a', R, 'q_out'], ' ': ['a', R, 'q_out']},
    'q4': {'a': ['a', L, 'q5']},
    'q5': {'a': ['a', L, 'q6']},
    'q6': {'a': ['b', R, 'q_out'], 'b': ['b', R, 'q_out'], 'c': ['b', R, 'q_out'], ' ': ['b', R, 'q_out']},
    'q10': {'a': ['a', L, 'q11']},
    'q11': {'a': ['a', L, 'q12']},
    'q12': {'a': ['c', R, 'q_out'], 'b': ['c', R, 'q_out'], 'c': ['c', R, 'q_out'], ' ': ['c', R, 'q_out']},
}

lenta = list(input())[::-1]
current_state = "q1"
i = 0
space = list(' ')
lenta = space + lenta + space
while current_state != 'q_out':
    current_symbol = lenta[i];
    step = states[current_state][current_symbol];
    lenta[i] = step[0]
    i += step[1]
    if i == len(lenta):
        lenta = lenta + space
    current_state = step[2]
lenta.pop(0)
lenta.pop(len(lenta) - 1)
print(*lenta[::-1], sep='')