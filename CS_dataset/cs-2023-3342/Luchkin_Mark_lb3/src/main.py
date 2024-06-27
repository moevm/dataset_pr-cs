moves = {'R': 1, 'L': -1, 'N': 0}

d = {
    'q1': {'a': 'a;N;q2', 'b': 'b;N;q2', 'c': 'c;N;q2', ' ': ' ;R;q1'}, 
    'q2': {'a': 'a;R;q2', 'b': 'b;R;qX', 'c': 'c;R;q2', ' ': ' ;L;q10'}, 
    'qX': {'a': 'a;N;q3', 'b': 'b;N;q3', 'c': 'c;N;q3', ' ': ' ;L;qY'}, 
    'qY': {'b': ' ;N;q12'},
    'q3': {'a': 'a;RR;q4', 'b': 'b;RR;q4', 'c': 'c;RR;q4', ' ': ' ;N;q12'}, 
    'q4': {'a': 'a;LL;q6', 'b': 'b;LL;q7', 'c': 'c;LL;q8', ' ': ' ;LL;q9'}, 
    'q5': {'b': ' ;N;q12'},
    'q6': {'a': 'a;R;q3', 'b': 'a;R;q3', 'c': 'a;R;q3'},
    'q7': {'a': 'b;R;q3', 'b': 'b;R;q3', 'c': 'b;R;q3'},
    'q8': {'a': 'c;R;q3', 'b': 'c;R;q3', 'c': 'c;R;q3'},
    'q9': {'a': ' ;R;q3', 'b': ' ;R;q3', 'c': ' ;R;q3'},
    'q10': {'a': 'a;L;q10', 'b': 'b;L;q10', 'c': 'c;L;q10', ' ': ' ;R;q11'}, 
    'q11': {'a': ' ;N;q12', 'b': ' ;N;q12', 'c': ' ;N;q12'},
    
    }

def turingMachine(tape):
    state = 'q1'
    head = 0
    while state != 'q12':
        symbol, directions, newState = d[state][tape[head]].split(';')
        
        tape[head] = symbol
        for i in directions:
            head += moves[i]
        state = newState


tape = [' '] + list(input()) + [' '] + [' ']
turingMachine(tape)
print(''.join(tape[1:-1]))    
