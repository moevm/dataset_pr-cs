import numpy as np
import math


def check_collision(bot1, bot2):
    a1, b1, c1 = bot1
    a2, b2, c2 = bot2
    
    matrix_1 = np.array([(a1, b1),
                         (a2, b2)])
    matrix_2 = np.array([-c1, -c2])

    if np.linalg.matrix_rank(matrix_1) < 2:
        return None
    else:
        x, y = np.linalg.solve(matrix_1, matrix_2)
        return round(x, 2), round(y, 2)


def check_surface(point1, point2, point3):
    x1, y1, z1 = point1
    x2, y2, z2 = point2
    x3, y3, z3 = point3

    matrix_coefs = np.array([(x1, y1, 1),
                             (x2, y2, 1),
                             (x3, y3, 1)])
    vec = np.array([(z1), (z2), (z3)])
    if np.linalg.matrix_rank(matrix_coefs) < 3:
        return None
    else:
        result = np.linalg.solve(matrix_coefs, vec)
        a, b, c = result
        return np.array([round(a, 2), round(b, 2), round(c,2)])


def check_rotation(vec, rad):
    matrix = np.array([(math.cos(rad), -math.sin(rad), 0),
                       (math.sin(rad), math.cos(rad), 0),
                       (0, 0, 1)])
    result = np.dot(matrix, vec)
    x, y, z = result
    return np.array([round(x, 2), round(y, 2), round(z, 2)])
