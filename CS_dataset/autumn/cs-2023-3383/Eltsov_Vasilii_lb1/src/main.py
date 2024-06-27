import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    x, y = robot
    x1 = min(point1[0], point2[0])
    x2 = max(point1[0], point2[0])
    y1 = min(point2[1], point3[1])
    y2 = max(point2[1], point3[1])
    return ((x1 <= x <= x2) and (y1 <= y <= y2))

def rank(a):
    return np.linalg.matrix_rank(a) == 2


def check_collision(coefficients):
    crash = []
    for i in range(len(coefficients)):
        for j in range(i + 1, len(coefficients)):
            m = [[coefficients[i][0], coefficients[i][1]], [coefficients[j][0], coefficients[j][1]]]
            if rank(m):
                crash.append((i, j))
                crash.append((j, i))
    return sorted(crash)


def check_path(points_list):
    path=0
    for i in range(len(points_list)-1):
        path+=np.linalg.norm(np.array(points_list[i]) - np.array(points_list[i+1]))
    return round(path, 2)