R, L, N = 1, -1, 0
table = {
    "q1": {"a": ("a", N, "q2"), "b": ("b", N, "q2"), "c": ("c", N, "q2"), " ": (" ", R, "q1")},
    "q2": {"a": ("*", L, "q3"), "b": ("*", L, "q4"), "c": ("*", L, "q5")," ": (" ", L, "q7"), "*": ("*", R, "q2")},
    "q3": {"a": ("a", L, "q3"), "b": ("b", L, "q3"), "c": ("c", L, "q3"), " ": ("a", R, "q6"), "*": ("*", L, "q3")},
    "q4": {"a": ("a", L, "q4"), "b": ("b", L, "q4"), "c": ("c", L, "q4"), " ": ("b", R, "q6"), "*": ("*", L, "q4")},
    "q5": {"a": ("a", L, "q5"), "b": ("b", L, "q5"), "c": ("c", L, "q5"), " ": ("c", R, "q6"), "*": ("*", L, "q5")},
    "q6": {"a": ("a", R, "q6"), "b": ("b", R, "q6"), "c": ("c", R, "q6"), " ": (" ", L, "q7"), "*": ("*", R, "q2")},
    "q7": {"a": ("a", N, "q8"), "b": ("b", N, "q8"), "c": ("c", N, "q8"), "*": (" ", L, "q7")}
}

memory = 13 * [" "] + list(input())
index = 0
state = "q1"
state_table = ["q1"]

while (state != "q8"):
    values = table[state][memory[index]]
    state_table.append(values[2])
    memory[index] = values[0]
    index += values[1]
    state = state_table[-1]

print("".join(memory))