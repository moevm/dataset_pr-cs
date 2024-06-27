import numpy as np


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

    matr_coef = np.array([(x1, y1, 1),
                          (x2, y2, 1),
                          (x3, y3, 1)])
    v = np.array([(z1), (z2), (z3)])

    if np.linalg.matrix_rank(matr_coef) < 3:
        return None

    result = np.linalg.solve(matr_coef, v)
    a, b, c = result

    return np.array([round(a, 2), round(b, 2), round(c, 2)])


def check_rotation(vec, rad):
    rotation_matrix = np.array([[np.cos(rad), -np.sin(rad), 0],
                                [np.sin(rad), np.cos(rad), 0],
                                [0, 0, 1]])

    rotated_coordinates = np.dot(rotation_matrix, vec)
    rounded_coordinates = np.round(rotated_coordinates, 2)

    return rounded_coordinates
