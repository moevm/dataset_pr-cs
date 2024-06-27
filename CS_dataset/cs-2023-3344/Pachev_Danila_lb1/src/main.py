import numpy as np
from math import cos, sin


def check_collision(bot1, bot2):
    koef_matrix = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    free_member_matrix = np.array([-bot1[2], -bot2[2]])
    if np.linalg.matrix_rank(koef_matrix) < 2:
        return None
    return tuple(round(value, 2) for value in list(np.linalg.solve(koef_matrix, free_member_matrix)))


def check_surface(point1, point2, point3):
    koef_matrix = np.array([[point1[0], point1[1], 1],[point2[0], point2[1], 1],[point3[0], point3[1], 1],])
    free_member_matrix = np.array([point1[2], point2[2], point3[2]])
    if np.linalg.matrix_rank(koef_matrix) < 3:
        return None
    return np.array(list(round(value, 2) for value in list(np.linalg.solve(koef_matrix, free_member_matrix))))


def check_rotation(vec, rad):
    rotate_matrix = np.array([[cos(rad), -sin(rad), 0], [sin(rad), cos(rad), 0], [0, 0, 1]])
    multi_matrix = np.dot(rotate_matrix, vec)
    return np.array(list(round(value, 2) for value in multi_matrix))
