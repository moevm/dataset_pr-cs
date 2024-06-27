import numpy as np
import math


def check_collision(bot1, bot2):
    a = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    b = np.array([-bot1[2], -bot2[2]])
    if np.linalg.matrix_rank(a) == 2:
        return tuple(np.linalg.solve(a, b).round(2))
    else:
        return None


def check_surface(point1, point2, point3):
    a = np.array([[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]])
    b = np.array([point1[2], point2[2], point3[2]])
    if np.linalg.matrix_rank(a) == 3:
        return np.array(np.linalg.solve(a, b).round(2))
    else:
        return None


def check_rotation(vec, rad):
    x=rad
    a=np.array([vec[0], vec[1], vec[2]])
    b=np.array([[math.cos(x), math.sin(x), 0], [-math.sin(x), math.cos(x), 0], [0, 0, 1]])
    return np.array(np.linalg.solve(b, a).round(2))
