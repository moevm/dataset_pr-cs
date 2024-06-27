import numpy as np


def check_collision(bot1, bot2):
    mat1 = np.array([bot1[:2], bot2[:2]])
    mat2 = np.array([-bot1[-1], -bot2[-1]])
    if np.linalg.matrix_rank(mat1) < len(mat1):
        return None
    answer = tuple(np.round(np.linalg.solve(mat1, mat2), 2))
    return answer


def check_surface(point1, point2, point3):
    mat1 = np.array([[*point1[:2], 1], [*point2[:2], 1], [*point3[:2], 1]])
    mat2 = np.array([point1[-1], point2[-1], point3[-1]])
    if np.linalg.matrix_rank(mat1) < len(mat1):
        return None
    answer = np.round(np.linalg.solve(mat1, mat2), 2)
    return answer


def check_rotation(vec, rad):
    mat = np.array([[np.cos(rad), -np.sin(rad), 0], [np.sin(rad), np.cos(rad), 0], [0, 0, 1]])
    answer = np.round(np.dot(mat, vec), 2)
    return answer