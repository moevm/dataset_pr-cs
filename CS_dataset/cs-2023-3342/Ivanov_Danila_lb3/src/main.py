dic = {
    'q1': {
        'a': ('a', 1, 'q2'),
        'b': ('b', 1, 'q2'),
        'c': ('c', 1, 'q2'),
        ' ': (' ', 1, 'q1')
    },
    'q2': {
        'a': ('a', 1, 'q2'),
        'b': ('b', 1, 'q2'),
        'c': ('c', 1, 'q2'),
        ' ': (' ', -1, 'q3')
    },
    'q3': {
        'a': ('a', -1, 'q4'),
        'b': ('b', -1, 'q3'),
        'c': ('c', -1, 'q3')
    },
    'q4': {
        'a': ('a', -1, 'q5'),
        'b': ('b', -1, 'q3'),
        'c': ('c', -1, 'q3')
    },
    'q5': {
        'a': ('a', 1, 'q6'),
        'b': ('b', 1, 'q7'),
        'c': ('c', 1, 'q8')
    },
    'q6': {
        'a': ('a', 1, 'q6'),
        'b': ('a', 0, 'q9'),
        'c': ('a', 0, 'q9'),
        ' ': ('a', 0, 'q9')
    },
    'q7': {
        'a': ('a', 1, 'q7'),
        'b': ('b', 0, 'q9'),
        'c': ('b', 0, 'q9'),
        ' ': ('b', 0, 'q9')
    },
    'q8': {
        'a': ('a', 1, 'q8'),
        'b': ('c', 0, 'q9'),
        'c': ('c', 0, 'q9'),
        ' ': ('c', 0, 'q9')
    }
}

a = list(input())
index = 0
sost = ['q1']
while True:
    new_s, step, new_sost = dic[sost[-1]][a[index]]
    a[index] = new_s
    index += step
    sost.append(new_sost)
    if sost[-1] == 'q9':
        break

print(''.join(a))