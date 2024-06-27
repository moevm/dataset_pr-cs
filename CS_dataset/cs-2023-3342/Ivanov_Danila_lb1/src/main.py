import numpy as np
from math import sin, cos


def check_collision(bot1, bot2):
    a1, a2, a3 = map(int, bot1)
    b1, b2, b3 = map(int, bot2)
    arr_1 = np.array([[a1, a2], [b1, b2]])
    arr_2 = np.array([-a3, -b3])
    if np.linalg.matrix_rank(arr_1) < 2:
        return None
    result = np.linalg.solve(arr_1, arr_2)
    return (round(result[0], 2), round(result[1], 2))


def check_surface(point1, point2, point3):
    a1, b1, z1 = map(int, point1)
    a2, b2, z2 = map(int, point2)
    a3, b3, z3 = map(int, point3)
    arr_1 = np.array([[a1, b1, 1], [a2, b2, 1], [a3, b3, 1]])
    arr_2 = np.array([z1, z2, z3])
    if np.linalg.matrix_rank(arr_1) < 3:
        return None
    result = np.linalg.solve(arr_1, arr_2)
    return np.array([round(result[0], 2), round(result[1], 2), round(result[2], 2)])


def check_rotation(vec, rad):
    arr = np.array([[cos(rad), -sin(rad), 0], [sin(rad), cos(rad), 0], [0, 0, 1]])
    result = np.dot(arr, vec)
    return np.array([round(result[0], 2), round(result[1], 2), round(result[2], 2)])