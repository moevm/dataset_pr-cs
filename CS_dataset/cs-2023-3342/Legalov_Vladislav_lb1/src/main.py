import numpy as np
from math import cos
from math import sin


def check_collision(bot1, bot2):
    data = np.vstack((bot1, bot2)).T
    ratio1 = data[0:2].T
    ratio2 = data[-1] * -1
    if np.linalg.matrix_rank(ratio1) != 2:
        return None
    else:
        return tuple([round(i, 2) for i in np.linalg.solve(ratio1, ratio2)])



def check_surface(point1, point2, point3):
    data = np.vstack((point1, point2, point3)).T
    ratio1 = np.vstack((data[0:2:], np.ones(3))).T
    ratio2 = data[-1]
    if np.linalg.matrix_rank(ratio1) != 3:
        return None
    else:
        return np.array([round(i, 2) for i in np.linalg.solve(ratio1, ratio2)])


def check_rotation(vec, rad):
    matrix_rotation = np.array([[cos(rad), -sin(rad), 0.], [sin(rad), cos(rad), 0.], [0., 0., 1.]])
    return np.array([round(i, 2) for i in np.dot(matrix_rotation, vec)])
