si = {
    'q1': 0,
    'q2': 1,
    'q3': 2,
    'q4': 3,
    'q5': 4,
    'q6': 5,
    'q7': 6, 
    'q8': 7,
}

vi = {
    'a': 0,
    'b': 1,
    'c': 2,
    ' ': 3
}

d = {
    'R': 1,
    'L': -1,
    'N': 0
}

table = """aR2;bR2;cR2; R1
aR2;bR2;cR2; L3
aL4;bL3;cL3
aL5;bL3;cL3
aR6;bR7;cR8
aR6;aR9;aR9;aR9
aR7;bR9;bR9;bR9
aR8;cR9;cR9;cR9"""

table = [[[j[0], j[1], 'q'+j[2]] for j in i.split(";")] for i in table.split("\n")]

cmd = list(input())
i = 0
h = ['q1']

while h[-1] != 'q9': 
    v = cmd[i]
    s = h[-1]
    c = table[si[s]][vi[v]]
    
    cmd[i] = c[0]
    i += d[c[1]]
    h.append(c[2])

print(''.join(cmd))