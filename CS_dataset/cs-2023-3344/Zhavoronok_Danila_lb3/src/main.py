s = list(input())
state = "st1"
index = 0
states = {
    "st1": {"a": ["a", 1, "st2"], "b": ["b", 1, "st2"], "c": ["c", 1, "st2"], " ": [" ", 1, "st1"]},
    "st2": {"a": ["a", 1, "st2"], "b": ["b", 1, "st2"], "c": ["c", 1, "st2"], " ": [" ", -1, "st3"]},
    "st3": {"a": ["a", -1, "st4"], "b": ["b", -1, "st3"], "c": ["c", -1, "st3"]},
    "st4": {"a": ["a", -1, "st5"], "b": ["b", -1, "st3"], "c": ["c", -1, "st3"]},
    "st5": {"a": ["a", 1, "st6"], "b": ["b", 1, "st7"], "c": ["c", 1, "st8"]},
    "st6": {"a": ["a", 1, "st6"], "b": ["a", 0, "st9"], "c": ["a", 0, "st9"], " ": ["a", 0, "st9"]},
    "st7": {"a": ["a", 1, "st7"], "b": ["b", 0, "st9"], "c": ["b", 0, "st9"], " ": ["b", 0, "st9"]},
    "st8": {"a": ["a", 1, "st8"], "b": ["c", 0, "st9"], "c": ["c", 0, "st9"], " ": ["c", 0, "st9"]}
}

while state != "st9":
    symbol, step, state = states[state][s[index]]
    s[index] = symbol
    index += step

print("".join(s))
