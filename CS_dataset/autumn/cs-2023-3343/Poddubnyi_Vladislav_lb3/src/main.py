L = -1
N = 0
R = 1

states = {
    # start parsing
    'q1': {'a': ['a', R, 'q2'], 'b': ['b', R, 'q1'], 'c': ['c', R, 'q1'], ' ': [' ', R, 'q1']},
    'q2': {'a': ['a', R, 'q3'], 'b': ['b', R, 'q1'], 'c': ['c', R, 'q1'], ' ': [' ', R, 'q1']},

    # founded
    'q3': {'a': ['a', L, 'q7'], 'b': ['b', L, 'q4'], 'c': ['c', L, 'q10'], ' ': [' ', L, 'q7']},

    # a
    'q7': {'a': ['a', L, 'q8']},
    'q8': {'a': ['a', L, 'q9']},
    'q9': {'a': ['a', R, 'qx'], 'b': ['a', R, 'qx'], 'c': ['a', R, 'qx'], ' ': ['a', R, 'qx']},
    # b
    'q4': {'a': ['a', L, 'q5']},
    'q5': {'a': ['a', L, 'q6']},
    'q6': {'a': ['b', R, 'qx'], 'b': ['b', R, 'qx'], 'c': ['b', R, 'qx'], ' ': ['b', R, 'qx']},
    # c
    'q10': {'a': ['a', L, 'q11']},
    'q11': {'a': ['a', L, 'q12']},
    'q12': {'a': ['c', R, 'qx'], 'b': ['c', R, 'qx'], 'c': ['c', R, 'qx'], ' ': ['c', R, 'qx']},
}

arr = list(input())[::-1]
state = "q1"
i = 0
space = list(' ')
arr = space + arr + space
while state != 'qx':
    current = arr[i];
    actions = states[state][current];
    arr[i] = actions[0]
    i += actions[1]
    if i == len(arr):
        arr = arr + space
    state = actions[2]
arr.pop(0)
arr.pop(len(arr) - 1)
print(*arr[::-1], sep='')
