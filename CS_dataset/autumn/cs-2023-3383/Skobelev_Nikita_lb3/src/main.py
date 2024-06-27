def alf(c):
    al = 'abc r'
    return al.find(c)


step = [
    [1, 0, 0, 1, 0],  # start
    [1, 1, 1, 0, 0],  # start_pos
    [-1, -1, -1, 0, 0],  # back_r
    [0, 0, 0, 0, -1],  # skip_r
    [1, 1, 1, 0, 1],  # A
    [1, 1, 1, 0, 1],  # B
    [1, 1, 1, 0, 1],  # C
    [1, 1, 1, 1, 1],  # back
]
condition = [
    [2, 0, 0, 1, 0],  # start
    [2, 2, 2, 3, 0],  # start_pos
    [3, 3, 3, 0, 4],  # back_r
    [5, 6, 7, 8, 4],  # skip_r
    [5, 5, 5, 3, 5],  # A
    [6, 6, 6, 3, 6],  # B
    [7, 7, 7, 3, 7],  # C
    [9, 9, 9, 0, 8],  #clear
]
ch = [
    'a    ',
    'abcr ',
    'abc r',  # back_r
    'rrr r',  # skip_r
    'abcar',  # A
    'abcbr',  # B
    'abccr',  # C
    'abc  ',  #clear
]

a = list(input())+[' ']*500
it_tek = 0
condition_tek = 1

while condition_tek != 9:
    a[it_tek],condition_tek,it_tek=ch[condition_tek - 1][alf(a[it_tek])],condition[condition_tek - 1][alf(a[it_tek])],it_tek + step[condition_tek - 1][alf(a[it_tek])]

print(''.join(a))