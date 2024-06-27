s = list(input())
state = "q1"
index = 0

states = {
    "q1" : {
        "a" : ["a", 1, "q2"], 
        "b" : ["b", 1, "q2"], 
        "c" : ["c", 1, "q2"], 
        " " : [" ", 1, "q1"]
    },
    "q2" : {
        "a" : ["a", 1, "q2"], 
        "b" : ["b", 1, "q2"], 
        "c" : ["c", 1, "q2"], 
        " ": [" ", -1, "q3"]
    },
    "q3" : {
        "a" : ["a", -1, "q4"], 
        "b" : ["b", -1, "q3"], 
        "c" : ["c", -1, "q3"]
    },
    "q4" : {
        "a" : ["a", -1, "q5"], 
        "b" : ["b", -1, "q3"], 
        "c": ["c", -1, "q3"]
    },
    "q5" : {
        "a" : ["a", 1, "q6"], 
        "b" : ["b", 1, "q7"], 
        "c" : ["c", 1, "q8"]
    },
    "q6" : {
        "a" : ["a", 1, "q6"], 
        "b" : ["a", 0, "qT"], 
        "c" : ["a", 0, "qT"], 
        " " : ["a", 0, "qT"]
    },
    "q7" : {
        "a" : ["a", 1, "q7"], 
        "b" : ["b", 0, "qT"], 
        "c" : ["b", 0, "qT"], 
        " " : ["b", 0, "qT"]
    },
    "q8" : {
        "a" : ["a", 1, "q8"], 
        "b" : ["c", 0, "qT"], 
        "c" : ["c", 0, "qT"], 
        " " : ["c", 0, "qT"]
    }
}

while state != "qT":
    symbol, step, state = states[state][s[index]]
    s[index]=symbol
    index += step

print("".join(s))