memory = list(str(input()))
state = "q0"
index = 0
table = {
    "q0": {
        "a" : ("a", "R", "q1"),
        "b" : ("b", "R", "q1"), 
        "c" : ("c", "R", "q1"), 
        ' ' : (" ", "R", "q0")
    },
    "q1" : {
        "a" : ("a", "R", "q1"),
        "b" : ("b", "R", "q1"), 
        "c" : ("c", "R", "q1"),
        " " : (" ", "L", "q2")
    },
    "q2": {
        "a" : ("a", "L", "q3"),
        "b" : ("b", "L", "q2"), 
        "c" : ("c", "L", "q2"), 
    },
    "q3" : {
        "a" : ("a", "L", "q4"),
        "b" : ("b", "L", "q2"), 
        "c" : ("c", "L", "q2"), 
    },
    "q4" : {
        "a" : ("a", "R", "q5"),
        "b" : ("b", "R", "q6"), 
        "c" : ("c", "R", "q7")
    },
    "q5" : {
        "a" : ("a", "R", "q5"),
        "b" : ("a", "N", "qT"), 
        "c" : ("a", "N", "qT"),
        " " : ("a", "N", "qT")
        },
    "q6" : {
        "a" : ("a", "R", "q6"),
        "b" : ("b", "N", "qT"), 
        "c" : ("b", "N", "qT"), 
        ' ' : ("b", "N", "qT")
    },
    "q7" : {
        "a" : ("a", "R", "q7"),
        "b" : ("c", "N", "qT"), 
        "c" : ("c", "N", "qT"), 
        ' ' : ("c", "N", "qT")
    }
}
while state != "qT":
    symbol = memory[index]
    new_symbol, delta, new_state = table[state][symbol]
    memory[index] = new_symbol
    if delta == "R":
        index += 1
    elif delta == "L":
        index -= 1
    state = new_state
print("".join(memory))
