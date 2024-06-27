import numpy
import numpy as np


def check_collision(bot1, bot2):
    a = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    b = np.array([-bot1[2], -bot2[2]])
    if np.linalg.matrix_rank(a) >= 2:
        return tuple(np.round(numpy.linalg.solve(a, b), 2))
    return "None"


def check_surface(point1, point2, point3):
    matrix = np.array([[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]])
    vector = np.array([point1[2], point2[2], point3[2]])
    if np.linalg.matrix_rank(matrix) >= 3:
        surface = np.linalg.solve(matrix, vector)
        return np.round(surface, 2)
    return "None"


def check_rotation(vec, rad):
    rotation = np.array([[np.cos(rad), -1 * np.sin(rad)], [np.sin(rad), np.cos(rad)]])
    coordinates = np.array(vec[:2])
    ans = np.dot(rotation, coordinates)
    ans = np.append(ans, vec[2])
    return np.round(ans, 2)
