lenta = list(input())
state = "qs"
index = 0
states = {'qs': {'a': ('a', 1, 'q1'), 'b': ('b', 1, 'q6'), 'c': ('c', 1, 'q1'), ' ': (' ', 1, 'qs')},
          'q1': {'a': ('a', 1, 'q1'), 'b': ('b', 1, 'q6'), 'c': ('c', 1, 'q1'), ' ': (' ', -1, 'q2')},
          'q2': {'a': ('a', -1, 'q2'), 'c': ('c', -1, 'q2'), ' ': (' ', 1, 'q3')},
          'q3': {'a': (' ', 1, 'q4'), 'c': (' ', 1, 'q4'), ' ': (' ', 1, 'q4')},
          'q4': {'a': (' ', -1, 'q5a'), 'c': (' ', -1, 'q5c'), ' ': (' ', 1, 'qe')},
          'q5a': {' ': ('a', 1, 'q3')},
          'q5c': {' ': ('c', 1, 'q3')},
          'q6': {'a': (' ', 1, 'q8'), 'b': (' ', 1, 'q8'), 'c': (' ', 1, 'q8'), ' ': (' ', -1, 'q7')},
          'q7': {'b': (' ', 1, 'qe')},
          'q8': {'a': ('a', 0, 'q10'), 'b': ('b', 0, 'q10'), 'c': ('c', 0, 'q10'), ' ': (' ', -1, 'q9')},
          'q9': {'a': (' ', 1, 'qe'), 'b': (' ', 1, 'qe'), 'c': (' ', 1, 'qe'), ' ': (' ', 1, 'qe')},
          'q10': {'a': (' ', 1, 'q11'), 'b': (' ', 1, 'q11'), 'c': (' ', 1, 'q11'), ' ': (' ', 1, 'q11')},
          'q11': {'a': (' ', -1, 'q12a'), 'b': (' ', -1, 'q12b'), 'c': (' ', -1, 'q12c'), ' ': (' ', -1, 'q12sp')},
          'q12a': {' ': ('a', 1, 'q10')},
          'q12b': {' ': ('b', 1, 'q10')},
          'q12c': {' ': ('c', 1, 'q10')},
          'q12sp': {' ': (' ', -1, 'q13')},
          'q13': {'a': ('a', -1, 'q13'), 'b': ('b', -1, 'q13'), 'c': ('c', -1, 'q13'), ' ': (' ', 0, 'q14')},
          'q14': {'a': (' ', 1, 'q15'), 'b': (' ', 1, 'q15'), 'c': (' ', 1, 'q15'), ' ': (' ', 1, 'q15')},
          'q15': {'a': (' ', -1, 'q16a'), 'b': (' ', -1, 'q16b'), 'c': (' ', -1, 'q16c'), ' ': (' ', 1, 'qe')},
          'q16a': {' ': ('a', 1, 'q14')},
          'q16b': {' ': ('b', 1, 'q14')},
          'q16c': {' ': ('c', 1, 'q14')}
}

while state != "qe":
    symbol, step, state = states[state][lenta[index]]
    lenta[index] = symbol
    index += step

print("".join(lenta))