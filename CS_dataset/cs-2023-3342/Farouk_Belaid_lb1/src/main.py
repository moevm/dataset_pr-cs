from math import sqrt

import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    points = [point1, point2, point3, point4]
    y_down = min(points, key=lambda x: x[1])[1]
    y_up = max(points, key=lambda x: x[1])[1]
    x_left = min(points, key=lambda x: x[0])[0]
    x_right = max(points, key=lambda x: x[0])[0]
    return ((x_left <= robot[0] <= x_right) and (y_down <= robot[1] <= y_up))


def check_collision(coefficients):
    result = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            traect1 = np.array(list(coefficients[i])[:2])
            traect2 = np.array(list(coefficients[j])[:2])
            matrix = np.vstack((traect1, traect2))
            if np.linalg.matrix_rank(matrix) == 2:
                result.append((i, j))
    return result


def check_path(points_list):
    result = 0
    for i in range(len(points_list) - 1):
        cur_p = points_list[i]
        next_p = points_list[i + 1]
        result += sqrt(abs(cur_p[0] - next_p[0]) ** 2 + abs(cur_p[1] - next_p[1]) ** 2)
    return round(result, 2)