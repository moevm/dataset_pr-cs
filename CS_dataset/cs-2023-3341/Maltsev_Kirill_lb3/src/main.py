moves = {'R': 1, 'L': -1, 'N': 0}

d = {
    'q1': {'a': 'a;R;q2', 'b': 'b;R;q2', 'c': 'c;R;q2', ' ': ' ;R;q1'}, # вход в область буквенных символов
    'q2': {'a': 'a;R;q2', 'b': 'b;R;q2', 'c': 'c;R;q2', ' ': ' ;L;q3'}, # смещение коретки на пробел
    'q3': {'a': 'a;L;q4', 'b': 'b;L;q3', 'c': 'c;L;q3'}, # поиск крайнего левого символа 'a' (переход к состоянию q4)
    'q4': {'a': 'a;L;q5', 'b': 'b;L;q3', 'c': 'c;L;q3'}, # проверка символа перед крайним левым символом 'a' (если 'a', то перейти к q5, если нет - q3)
    'q5': {'a': 'a;RRR;q6', 'b': 'b;RRR;q7', 'c': 'c;RRR;q8'}, # "запоминание" символа перед крайним 'aa' - переход к соответствующему состоянию q6, q7 или q8
    'q6': {'a': 'a;N;q9', 'b': 'a;N;q9', 'c': 'a;N;q9', ' ': 'a;N;q9'}, # замена на a
    'q7': {'a': 'b;N;q9', 'b': 'b;N;q9', 'c': 'b;N;q9', ' ': 'b;N;q9'}, # замена на b
    'q8': {'a': 'c;N;q9', 'b': 'c;N;q9', 'c': 'c;N;q9', ' ': 'c;N;q9'}, # замена на c
    }


def turing_machine(tape):
    state = 'q1'
    head = 0
    while state != 'q9':
        symbol, directions, new_state = d[state][tape[head]].split(';')
        
        tape[head] = symbol
        for i in directions:
            head += moves[i]
        state = new_state


def main():
    tape = [' '] + list(input()) + [' ']
    turing_machine(tape)
    print(''.join(tape[1:-1]))    


if __name__ == '__main__':
    main()
