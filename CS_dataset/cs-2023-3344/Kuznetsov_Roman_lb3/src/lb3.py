tape = list(input())

machine = {
    #ищем а
    "q_start": {"a": ("a", "R", "q_after_a"), "b": ("b", "R", "q_start"), "c": ("c", "R", "q_start"), " ": (" ", "R", "q_start")},
    # символ после а
    "q_after_a": {"a": ("a", "N", "q_a.1"), "b": ("b", "N", "q_b.1"), "c": ("c", "N", "q_c.1"), " ": (" ", "L", "q_void")},
    #вставляем а
    "q_a.1": {"a": ("a", "L", "q_a.1"), "b": ("b", "L", "q_a.1"), "c": ("c", "L", "q_a.1"), " ": (" ", "R", "q_a.2")},
    "q_a.2": {"a": ("a", "R", "q_a.2"), "b": ("b", "R", "q_a.2"), "c": ("c", "L", "q_a.3")},
    "q_a.3": {"a": ("a", "N", "q_end"), "b": ("a", "N", "q_end"), "c": ("a", "N", "q_end"), " ": ("a", "N", "q_end")},
    #вставляем б
    "q_b.1": {"a": ("a", "L", "q_b.1"), "b": ("b", "L", "q_b.1"), "c": ("c", "L", "q_b.1"), " ": (" ", "R", "q_b.2")},
    "q_b.2": {"a": ("a", "R", "q_b.2"), "b": ("b", "R", "q_b.2"), "c": ("c", "L", "q_b.3")},
    "q_b.3": {"a": ("b", "N", "q_end"), "b": ("b", "N", "q_end"), "c": ("b", "N", "q_end"), " ": ("b", "N", "q_end")},
    #вставляем с
    "q_c.1": {"a": ("a", "L", "q_c.1"), "b": ("b", "L", "q_c.1"), "c": ("c", "L", "q_c.1"), " ": (" ", "R", "q_c.2")},
    "q_c.2": {"a": ("a", "R", "q_c.2"), "b": ("b", "R", "q_c.2"), "c": ("c", "L", "q_c.3")},
    "q_c.3": {"a": ("c", "N", "q_end"), "b": ("c", "N", "q_end"), "c": ("c", "N", "q_end"), " ": ("c", "N", "q_end")},
    #если пробел
    "q_void": {"a": ("a", "L", "q_void"), "b": ("b", "L", "q_void"), "c": ("c", "L", "q_void"), " ": (" ", "R", "q_void.2")},
    "q_void.2": {"a": ("a", "R", "q_void.2"), "b": ("b", "R", "q_void.2"), "c": ("c", "L", "q_void.3")},
    "q_void.3": {"a": ("a", "N", "q_end"), "b": ("a", "N", "q_end"), "c": ("a", "N", "q_end"), " ": ("a", "N", "q_end")}
}

state = "q_start"
position = 0

while state != "q_end":
    insert_symbol, move, next_state = machine[state][tape[position]]
    tape[position] = insert_symbol
    
    position += 1 if move == "R" else -1 if move == "L" else 0
    
    state = next_state

print("".join(tape))
