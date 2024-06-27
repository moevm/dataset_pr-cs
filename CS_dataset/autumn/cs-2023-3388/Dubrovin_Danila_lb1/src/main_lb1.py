import numpy as np


def check_collision(bot1, bot2):
    matrix_bots = np.vstack((bot1, bot2))
    vector = np.array([-x for x in (matrix_bots[:, -1])])
    matrix_cf = matrix_bots[:, 0:2]
    if check_matrix(matrix_cf):
        return tuple(round(x, 2) for x in np.linalg.solve(matrix_cf, vector))
    else:
        return None


def check_surface(point1, point2, point3):
    matrix_cf = np.vstack((point1, point2, point3))
    vector = np.array([x for x in (matrix_cf[:, -1])])
    matrix_cf = np.hstack((matrix_cf[:, 0:1], matrix_cf[:, 1:2], np.array([[1], [1], [1]])))
    if check_matrix(matrix_cf):
        return np.array([round(x, 2) for x in np.linalg.solve(matrix_cf, vector)])
    else:
        return None


def check_rotation(vec, rad):
    rotation_z = np.array([[np.cos(rad), -np.sin(rad), 0],
                           [np.sin(rad), np.cos(rad), 0],
                           [0, 0, 1]])
    return np.array([round(x,2) for x in np.dot(rotation_z, vec)])


def check_matrix(matrix):
    return (np.linalg.matrix_rank(matrix)) == (len(matrix[0]))
