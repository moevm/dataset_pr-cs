import numpy as np
import math


def check_crossroad(robot, point1, point2, point3, point4):
    return point1[0] <= robot[0] <= point3[0] and point1[1] <= robot[1] <= point3[1]


def check_collision(coefficients):
    pairs = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            a1, b1, c1 = coefficients[i]
            a2, b2, c2 = coefficients[j]
            if np.linalg.matrix_rank(np.array([[a1, b1], [a2, b2]])) == 2:
                pairs.append((i, j))
    return sorted(pairs)


def check_path(points_list):
    path_length = 0
    for i in range(len(points_list) - 1):
        x1, y1 = points_list[i]
        x2, y2 = points_list[i + 1]
        path_length = path_length + math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
    return round(path_length, 2)
