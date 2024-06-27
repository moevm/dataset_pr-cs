tape = input()
shifts = {'L': -1, 'N': 0, 'R': 1}
state = "q0"
states = {
    'q0':{'a': ['a', 'R', 'qa'], 'b': ['b', 'R', 'q0'], 'c': ['c', 'R', 'q0'], ' ':[' ', 'R', 'q0']},
    'qa':{'a': ['a', 'L', 'qaa'], 'b': ['b', 'L', 'qab'], 'c': ['c', 'L', 'qac'], ' ':[' ', 'L', 'qaa']},
    'qaa': {'a': ['a', 'L', 'qaa'], 'b': ['b', 'L', 'qaa'], 'c': ['c', 'L', 'qaa'], ' ': [' ', 'R', 'qaaL']},
    'qab': {'a': ['a', 'L', 'qab'], 'b': ['b', 'L', 'qab'], 'c': ['c', 'L', 'qab'], ' ': [' ', 'R', 'qabL']},
    'qac': {'a': ['a', 'L', 'qac'], 'b': ['b', 'L', 'qac'], 'c': ['c', 'L', 'qac'], ' ': [' ', 'R', 'qacL']},
    'qaaL': {'a': ['a', 'R', 'qaaL'], 'b': ['b', 'R', 'qaaL'], 'c': ['c', 'L', 'qaaLc']},
    'qabL': {'a': ['a', 'R', 'qabL'], 'b': ['b', 'R', 'qabL'], 'c': ['c', 'L', 'qabLc']},
    'qacL': {'a': ['a', 'R', 'qacL'], 'b': ['b', 'R', 'qacL'], 'c': ['c', 'L', 'qacLc']},
    'qaaLc': {'a': ['a', 'N', 'qaaLca'], 'b': ['b', 'N', 'qaaLcb'], 'c': ['c', 'N', 'qaaLcc'], ' ': [' ', 'N', 'qaaLc_space' ]},
    'qabLc': {'a': ['a', 'N', 'qabLca'], 'b': ['b', 'N', 'qabLcb'], 'c': ['c', 'N', 'qabLcc'], ' ': [' ', 'N', 'qabLc_space']},
    'qacLc': {'a': ['a', 'N', 'qacLca'], 'b': ['b', 'N', 'qacLcb'], 'c': ['c', 'N', 'qacLcc'], ' ': [' ', 'N', 'qacLc_space']},
}

index = 0

while(not(state in ['qaaLc', 'qabLc', 'qacLc'])):
    symbol = tape[index]
    state_data = states[state][symbol]
    state = state_data[2]
    index += shifts[state_data[1]]

state_data = states[state][symbol]
index += shifts[state_data[1]]
tape = tape[:index] + state_data[2][2] + tape[index+1:]

print(tape)