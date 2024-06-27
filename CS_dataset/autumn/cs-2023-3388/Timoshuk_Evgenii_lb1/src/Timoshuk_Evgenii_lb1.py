import numpy as np


def check_collision(bot1, bot2):
    matrix = np.array((bot1[:2], bot2[:2]))
    vector = np.array((-bot1[2], -bot2[2]))
    rank = np.linalg.matrix_rank(matrix)
    if rank != 2:
        return None
    else:
        result = np.linalg.solve(matrix, vector)
        result = np.around(result, 2)
        result = tuple(result)
        return result


def check_surface(point1, point2, point3):
    matrix = np.array([[point1[0], point1[1], 1],
                       [point2[0], point2[1], 1],
                       [point3[0], point3[1], 1]])
    vector = np.array((point1[2], point2[2], point3[2]))
    if np.linalg.matrix_rank(matrix) == 3:
        return np.around(np.linalg.solve(matrix, vector), 2)
    return None

def check_rotation(vec, rad):
    matrix = np.array([[np.cos(rad), -np.sin(rad), 0],[np.sin(rad), np.cos(rad), 0],[0, 0, 1]])
    result = np.around(np.dot(matrix, vec), 2)
    return result