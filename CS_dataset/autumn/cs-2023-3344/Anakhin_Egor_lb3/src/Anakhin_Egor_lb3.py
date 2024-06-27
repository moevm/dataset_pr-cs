LEFT, STOP, RIGHT = -1, 0, 1

states = {

    ("q0", " "): (' ', RIGHT, "q0"),
    ("q0", "a"): ('a', STOP, "q1"),
    ("q0", "b"): ('b', RIGHT, "b_found"),
    ("q0", "c"): ('c', STOP, "q1"),

    ("q1", " "): (' ', LEFT, "b_not_found"),
    ("q1", "a"): ('a', RIGHT, "q1"),
    ("q1", "b"): ('b', RIGHT, "b_found"),
    ("q1", "c"): ('c', RIGHT, "q1"),

    ("b_found", " "): (' ', LEFT, "b_last"),
    ("b_found", "a"): (' ', RIGHT, "first_deleted"),
    ("b_found", "b"): (' ', RIGHT, "first_deleted"),
    ("b_found", "c"): (' ', RIGHT, "first_deleted"),

    ("first_deleted", " "): (' ', STOP, "finished"),
    ("first_deleted", "a"): (' ', STOP, "finished"),
    ("first_deleted", "b"): (' ', STOP, "finished"),
    ("first_deleted", "c"): (' ', STOP, "finished"),

    ("b_last", "b"): (' ', STOP, 'finished'),

    ("b_not_found", " "): (' ', RIGHT, "first_word"),
    ("b_not_found", "a"): ('a', LEFT, "b_not_found"),
    ("b_not_found", "b"): ('b', LEFT, "b_not_found"),
    ("b_not_found", "c"): ('c', LEFT, "b_not_found"),

    ("first_word", "a"): (' ', STOP, 'finished'),
    ("first_word", "c"): (' ', STOP, 'finished'),

}

string = list(' ' + input() + ' ')
position = 0
state = 'q0'

while state != 'finished':

    symbol, move, state_after = states[(state, string[position])]
    string[position] = symbol
    position += move
    state = state_after

print(''.join(string).replace(" ", ""))