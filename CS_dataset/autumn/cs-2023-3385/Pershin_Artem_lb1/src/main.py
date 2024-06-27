import numpy as np
import math


def check_crossroad(robot, point1, point2, point3, point4):
    x, y = robot
    return (point1[0] <= x <= point3[0] and point1[1] <= y <= point3[1])



def check_collision(ndarray):
    s = []
    l = len(ndarray)
    for i in range(l):
        a1, b1, c1 = ndarray[i]
        for j in range(l):
            if i != j:
                a2, b2, c2 = ndarray[j]
                x = np.linalg.matrix_rank([[a1, b1], [a2, b2]])
                if x == 2:
                    s.append((i, j))
    return s


def check_path(points_list):
    l = 0
    for i in range(len(points_list) - 1):
        j = i + 1
        dx = points_list[j][0] - points_list[i][0]
        dy = points_list[j][1] - points_list[i][1]
        l += math.sqrt(dx ** 2 + dy ** 2)
    return round(l, 2)
