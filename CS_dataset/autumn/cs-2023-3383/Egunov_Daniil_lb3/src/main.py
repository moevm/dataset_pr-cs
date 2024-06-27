# q0 move to start of the original word
# q1 move to last symbol of the original word
# q2 capture last symbol before '.'
# q3 add 'a' to end
# q4 add 'b' to end
# q5 add 'c' to end
# q6 move to last '.'
# q7 delete all '.'


def main():
    table = {
        'q0': {'a': ('a', 1, 'q1'), 'b': ('b', 1, 'q1'), 'c': ('c', 1, 'q1'), ' ': (' ', 1, 'q0')},
        'q1': {'a': ('a', 1, 'q1'), 'b': ('b', 1, 'q1'), 'c': ('c', 1, 'q1'), ' ': (' ', -1, 'q2')},
        'q2': {'a': ('.', 1, 'q3'), 'b': ('.', 1, 'q4'), 'c': ('.', 1, 'q5'), ' ': (' ', 1, 'q7'), '.': ('.', -1, 'q2')},
        'q3': {'a': ('a', 1, 'q3'), 'b': ('b', 1, 'q3'), 'c': ('c', 1, 'q3'), ' ': ('a', -1, 'q6'), '.': ('.', 1, 'q3')},
        'q4': {'a': ('a', 1, 'q4'), 'b': ('b', 1, 'q4'), 'c': ('c', 1, 'q4'), ' ': ('b', -1, 'q6'), '.': ('.', 1, 'q4')},
        'q5': {'a': ('a', 1, 'q5'), 'b': ('b', 1, 'q5'), 'c': ('c', 1, 'q5'), ' ': ('c', -1, 'q6'), '.': ('.', 1, 'q5')},
        'q6': {'a': ('a', -1, 'q6'), 'b': ('b', -1, 'q6'), 'c': ('c', -1, 'q6'), '.': ('.', -1, 'q2')},
        'q7': {'a': ('a', 0, 'qT'), 'b': ('b', 0, 'qT'), 'c': ('c', 0, 'qT'), '.': (' ', 1, 'q7')},
    }

    memory = input()
    memory = list(' ' + memory + (' ' * (len(memory) + 1)))
    index = 0
    state = 'q0'

    while state != 'qT':
        symbol = memory[index]
        new_symbol, delta, state = table[state][symbol]
        memory[index] = new_symbol
        index += delta

    print(''.join(memory))


if __name__ == '__main__':
    main()

