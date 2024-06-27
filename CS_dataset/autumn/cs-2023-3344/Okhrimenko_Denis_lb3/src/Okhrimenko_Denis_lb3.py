R = 1
L = -R
N = 0
states = {
    "qStrt": {
        "a": ("a", R, "q1"),
        "b": ("b", R, "q6"),
        "c": ("c", R, "q1"),
        " ": (" ", R, "qStrt"),
    },
    "q1": {
        "a": ("a", R, "q1"),
        "b": ("b", R, "q6"),
        "c": ("c", R, "q1"),
        " ": (" ", L, "q2"),
    },
    "q2": {"a": ("a", L, "q2"), "c": ("c", L, "q2"), " ": (" ", R, "q3")},
    "q3": {"a": (" ", R, "q4"), "c": (" ", R, "q4"), " ": (" ", R, "q4")},
    "q4": {"a": (" ", L, "q5posta"), "c": (" ", L, "q5postc"), " ": (" ", R, "qEx")},
    "q5posta": {" ": ("a", R, "q3")},
    "q5postc": {" ": ("c", R, "q3")},
    "q6": {
        "a": (" ", R, "q8"),
        "b": (" ", R, "q8"),
        "c": (" ", R, "q8"),
        " ": (" ", L, "q7"),
    },
    "q7": {"b": (" ", R, "qEx")},
    "q8": {
        "a": ("a", 0, "q10"),
        "b": ("b", 0, "q10"),
        "c": ("c", 0, "q10"),
        " ": (" ", L, "q9"),
    },
    "q9": {
        "a": (" ", R, "qEx"),
        "b": (" ", R, "qEx"),
        "c": (" ", R, "qEx"),
        " ": (" ", R, "qEx"),
    },
    "q10": {
        "a": (" ", R, "q11"),
        "b": (" ", R, "q11"),
        "c": (" ", R, "q11"),
        " ": (" ", R, "q11"),
    },
    "q11": {
        "a": (" ", L, "q12posta"),
        "b": (" ", L, "q12postb"),
        "c": (" ", L, "q12postc"),
        " ": (" ", L, "q12postv"),
    },
    "q12posta": {" ": ("a", R, "q10")},
    "q12postb": {" ": ("b", R, "q10")},
    "q12postc": {" ": ("c", R, "q10")},
    "q12postv": {" ": (" ", L, "q13")},
    "q13": {
        "a": ("a", L, "q13"),
        "b": ("b", L, "q13"),
        "c": ("c", L, "q13"),
        " ": (" ", 0, "q14"),
    },
    "q14": {
        "a": (" ", R, "q15"),
        "b": (" ", R, "q15"),
        "c": (" ", R, "q15"),
        " ": (" ", R, "q15"),
    },
    "q15": {
        "a": (" ", L, "q16posta"),
        "b": (" ", L, "q16postb"),
        "c": (" ", L, "q16postc"),
        " ": (" ", R, "qEx"),
    },
    "q16posta": {" ": ("a", R, "q14")},
    "q16postb": {" ": ("b", R, "q14")},
    "q16postc": {" ": ("c", R, "q14")},
}
line = list(input())
state = "qStrt"
head = 0
direction = 0
ans_states = ["qStrt"]
while state != "qEx":
    line[head], direction, state = states[state][line[head]]
    head += direction
    ans_states += [state]
print("".join(line))
