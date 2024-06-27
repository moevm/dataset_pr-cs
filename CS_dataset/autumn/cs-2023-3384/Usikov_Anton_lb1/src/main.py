import numpy as np
from numpy import linalg  as lg


def check_collision(bot1, bot2):
    mtr = np.array([bot1[:2], bot2[:2]])
    svb = -np.array([bot1[2], bot2[2]])
    if lg.matrix_rank(mtr) == 2:
        return tuple(np.round(lg.solve(mtr, svb), 2))
    return None


def check_surface(point1, point2, point3):
    mtr = [[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]]
    svb = np.array([point1[2], point2[2], point3[2]])
    if lg.matrix_rank(mtr) == 3:
        return np.round(lg.solve(mtr, svb), 2)
    return None


def check_rotation(vec, rad):
    rmtr = np.array([[np.cos(rad), -np.sin(rad), 0],
                    [np.sin(rad), np.cos(rad), 0],
                    [0, 0, 1]])
    return np.round(np.dot(rmtr, vec), 2)