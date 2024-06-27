import numpy as np
from math import sin, cos


def check_collision(bot1, bot2):
    c = np.array([-1 * bot1[-1], -1 * bot2[-1]])
    a = np.vstack([bot1[0:2], bot2[0:2]])
    if np.linalg.matrix_rank(a) < 2:
        return None
    return tuple(np.linalg.solve(a, c).round(2))


def check_surface(point1, point2, point3):
    a = np.vstack((point1[0:2], (point2[0:2], point3[0:2])))
    a = np.hstack((a, [[1],[1],[1]]))
    b = np.array([[point1[-1]], [point2[-1]], [point3[-1]]])
    if np.linalg.matrix_rank(a) < 3:
        return None
    return np.array([i[0].round(2) for i in np.linalg.solve(a, b)])

        
def check_rotation(vec, rad):
    x, y, z = vec
    x_new = x * cos(rad) - y * sin(rad)
    y_new = x *sin(rad) + y * cos(rad)
    return np.array([x_new, y_new, z]).round(2);
