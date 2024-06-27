import numpy as np
from math import sin, cos


def check_collision(bot1, bot2):
    matrix = np.array([bot1[:2], bot2[:2]])
    ordinates = np.array([-bot1[2], -bot2[2]])

    rank = np.linalg.matrix_rank(matrix)
    if rank >= 2:
        answer = list(map(lambda x: round(x, 2), np.linalg.solve(matrix, ordinates)))
        return tuple(answer)


def check_surface(point1, point2, point3):
    matrix = np.array([
        [*point1[:2], 1],
        [*point2[:2], 1],
        [*point3[:2], 1]
    ])
    ordinates = np.array([
        point1[2],
        point2[2],
        point3[2]
    ])

    rank = np.linalg.matrix_rank(matrix)
    if rank >= 3:
        answer = list(map(lambda x: round(x, 2), np.linalg.solve(matrix, ordinates)))
        return np.asarray(answer)


def check_rotation(coordinates, angle):
    rotate_matrix = np.array([
        [cos(angle), -sin(angle), 0],
        [sin(angle), cos(angle), 0],
        [0, 0, 1]
    ])

    return np.asarray(list(map(lambda x: round(x, 2), np.dot(rotate_matrix, coordinates))))
