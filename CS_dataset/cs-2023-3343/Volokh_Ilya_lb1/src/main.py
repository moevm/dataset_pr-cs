import numpy as np

def check_if_longest(point1,point2, point3, point4, robot, longest):
    coun = 0
    c = (abs(point1[0] - robot[0]), abs(point1[1] - robot[1]))
    g = (abs(point2[0] - robot[0]), abs(point2[1] - robot[1]))
    z = (abs(point3[0] - robot[0]), abs(point3[1] - robot[1]))
    d = (abs(point4[0] - robot[0]), abs(point4[1] - robot[1]))
    ln1, ln2, ln3, ln4 = np.linalg.norm(c), np.linalg.norm(g), np.linalg.norm(z), np.linalg.norm(d)
    if ln1 > longest:
        coun += 1
    if ln2 > longest:
        coun += 1
    if ln3 > longest:
        coun += 1
    if ln4 > longest:
        coun += 1
    return coun
def check_if_width_length(point1,point2, point3, point4, robot, width, length):
    alot = [[abs(point1[0] - robot[0]), abs(point1[1] - robot[1])],[abs(point2[0] - robot[0]), abs(point2[1] - robot[1])], [abs(point3[0] - robot[0]), abs(point3[1] - robot[1])], [abs(point4[0] - robot[0]), abs(point4[1] - robot[1])] ]
    coun = 0
    x1, y1, x2, y2, x3, y3, x4, y4 = alot[0][0], alot[0][1], alot[1][0], alot[1][1], alot[2][0], alot[2][1], alot[3][0], alot[3][1]
    if x1 > width or y1 > length:
        coun += 1
    if x2 > width or y2 > length:
        coun += 1
    if x3 > width or y3 > length:
        coun += 1
    if x4 > width or y4 > length:
        coun += 1
    return coun
def check_crossroad(robot, point1, point2, point3, point4):
    c = (abs(point1[0] - point3[0]), abs(point1[1] - point3[1]))
    longest, width, length = np.linalg.norm(c), abs(point1[0] - point2[0]), abs(point4[1] - point1[1])
    count = 0
    if check_if_longest(point1,point2, point3, point4, robot, longest) > 1:
        return False
    else:
        count += 1
    if check_if_width_length(point1,point2, point3, point4, robot, width, length) > 0:
        return False
    else:
        count += 1
    if count == 2:
        return True
    else:
        return False

def thats_collision_man(a1, b1, c1, a2, b2, c2):
    A = np.array([[a1, b1], [a2, b2]])
    B = np.array([-c1, -c2])
    try:
        np.linalg.solve(A, B)
        return 1
    except:
        return 0

def check_collision(coefficients):
    azs, bzs, czs = [], [], []
    coefficients = coefficients.tolist()
    for i in coefficients:
            azs.append(int(i[0]))
            bzs.append(int(i[1]))
            czs.append(int(i[2]))
    collisions = []
    N = len(coefficients)
    for i in range(N - 1):
        for j in range(i + 1, N):
            if thats_collision_man(azs[i], bzs[i], czs[i],azs[j], bzs[j], czs[j]) == 1:
                collisions.append((i, j))
                collisions.append((j, i))
    collisions = sorted(collisions, key=lambda x: x[0])
    return collisions



def distance(x1, x2, y1, y2):
    dist = np.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
    return dist
def check_path(points_list):
    full_path = 0.0
    for i in range(len(points_list) - 1):
        x1, y1 = points_list[i]
        x2, y2 = points_list[i+1]
        if (x1 != x2 or y1 != y2) and ((x1, y1) != (x2, y2)):
            full_path += distance(x1, x2, y1, y2)
    return round(full_path, 2)
