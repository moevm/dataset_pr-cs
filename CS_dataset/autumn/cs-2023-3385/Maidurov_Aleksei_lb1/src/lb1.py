import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    x_min, y_min = point1
    x_max, y_max = point3
    x, y = robot
    return x_min <= x <= x_max and y_min <= y <= y_max


def check_collision(coefficients):
    n = len(coefficients)
    res = []
    for i in range(n):
        for j in range(n):
            a1, b1, c1 = coefficients[i]
            a2, b2, c2 = coefficients[j]
            if a1 * b2 != a2 * b1:
                res.append((i, j))
    return res


def check_path(points_list):
    x, y = points_list[0]
    res = 0
    for new_x, new_y in points_list[1:]:
        res += ((new_x - x) ** 2 + (new_y - y) ** 2) ** 0.5
        x, y = new_x, new_y
    return round(res, 2)
