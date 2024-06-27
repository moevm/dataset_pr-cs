import numpy as np
from math import sin, cos


def check_collision(bot1, bot2):
    try:
        t = np.vstack((bot1, bot2))
        ones, twos, eq = np.split(t, 3, 1)
        task = np.hstack((ones, twos))
        res = np.round(np.linalg.solve(task, -1*eq), 2)
        return tuple(map(float, res))
    except np.linalg.LinAlgError:
        return None


def check_surface(p1, p2, p3):
    try:
        co_matrix = np.vstack((p1, p2, p3))
        c = np.ones((3, 1))
        a, b, free = np.hsplit(co_matrix, 3)
        co_matrix = np.hstack((a, b, c))
        return np.transpose(np.round(np.linalg.solve(co_matrix, free), 2))[0]
    except np.linalg.LinAlgError:
        return None


def check_rotation(pos, r):
    try:
        r = -r
        rot_matrix = np.array([[ cos(r), -sin(r),  0],
                               [ sin(r),  cos(r),  0],
                               [ 0,       0,       1]])
        return np.round(np.dot(pos, rot_matrix), 2)
    except np.linalg.LinAlgError:
        return None