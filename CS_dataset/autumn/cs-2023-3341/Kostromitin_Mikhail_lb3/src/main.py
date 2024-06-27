statusDict = {
    'q1': {'a': 'a,N,q2', 'b': 'b,N,q2', 'c': 'c,N,q2', ' ': ' ,R,q1'},
    'q2': {'a': 'a,R,q2', 'b': 'b,R,q2', 'c': 'c,R,q2', ' ': ' ,L,q3'},
    'q3': {'a': 'a,L,q4', 'b': 'b,L,q3', 'c': 'c,L,q3', ' ': ' ,N,qn'},
    'q4': {'a': 'a,L,q5', 'b': 'b,L,q3', 'c': 'c,L,q3', ' ': ' ,N,qn'},
    'q5': {'a': 'a,R,q6', 'b': 'b,R,q7', 'c': 'c,R,q8', ' ': ' ,n,qn'},
    'q6': {'a': 'a,R,q6', 'b': 'b,N,q9', 'c': 'c,N,q9', ' ': ' ,N,q9'},
    'q7': {'a': 'a,R,q7', 'b': 'b,N,q10', 'c': 'c,N,q10', ' ': ' ,N,q10'},
    'q8': {'a': 'a,R,q8', 'b': 'b,N,q11', 'c': 'c,N,q11', ' ': ' ,N,q11'},
    'q9': {'a': 'a,N,q12', 'b': 'a,N,q12', 'c': 'a,N,q12', ' ': 'a,N,q12'},
    'q10': {'a': 'b,N,q12', 'b': 'b,N,q12', 'c': 'b,N,q12', ' ': 'b,N,q12'},
    'q11': {'a': 'c,N,q12', 'b': 'c,N,q12', 'c': 'c,N,q12', ' ': 'c,N,q12'},
    'q12': {'a': 'a,R,q12', 'b': 'b,R,q12', 'c': 'c,R,q12', ' ': ' ,N,qn'}
    }

moves = {'R': 1, 'L': -1, 'N': 0}

def turingMachine(lenta):
    state = 'q1'
    current = 0
    while state != 'qn':
        symbol, move, newState = statusDict[state][lenta[current]].split(',')
        lenta[current] = symbol
        current += moves[move]
        state = newState
    print(''.join(lenta[1:current]))


lenta = [' '] + list(input()) + [' '] + [' ']
turingMachine(lenta)