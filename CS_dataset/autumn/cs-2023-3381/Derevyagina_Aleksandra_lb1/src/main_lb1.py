import numpy as np


def check_collision(bot1, bot2):
    arr1 = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    arr2 = np.array([-bot1[2], -bot2[2]])
    if np.linalg.matrix_rank(arr1) == 2:
        return tuple(np.linalg.solve(arr1, arr2).round(2))
    return None


def  check_surface(point1, point2, point3):
    arr1 = np.array([[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]])
    arr2 = np.array([point1[2], point2[2], point3[2]])
    if np.linalg.matrix_rank(arr1) == 3:
        return np.linalg.solve(arr1, arr2).round(2)
    return None


def check_rotation(vector, rad):
    matrix = np.array([[np.cos(rad), -np.sin(rad), 0], [np.sin(rad), np.cos(rad), 0], [0, 0, 1]])
    return np.dot(matrix, vector).round(2)
