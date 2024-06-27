import numpy as np


def check_collision(bot1, bot2):
    if np.linalg.matrix_rank([bot1, bot2]) == 2:
        return tuple(np.round(np.linalg.solve([bot1[:2], bot2[:2]], [-bot1[2], -bot2[2]]), 2))
    else:
        return None


def check_surface(point1, point2, point3):
    matrix = np.ones((3, 3))
    vector = []
    for index, point in enumerate([point1, point2, point3]):
        matrix[index, :2] = point[:2]
        vector.append(point[2])
    if np.linalg.matrix_rank(matrix) == 3:
        return np.round(np.linalg.solve(matrix, vector), 2)
    else:
        return None


def check_rotation(vec, rad):
    sin = np.sin(rad)
    cos = np.cos(rad)
    rotation_matrix = np.array([[cos, -sin, 0], [sin, cos, 0], [0, 0, 1]])
    return np.round(rotation_matrix @ vec, 2)