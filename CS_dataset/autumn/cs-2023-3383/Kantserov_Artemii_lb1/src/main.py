import numpy as np


def check_collision(bot1, bot2):
    a = np.array([bot1[:2], bot2[:2]])
    b = np.array([-bot1[2], -bot2[2]])
    try:
        c = np.linalg.solve(a, b)
        c = np.round(c, 2)
        return tuple(c)
    except np.linalg.LinAlgError:
        return None
def check_surface(point1, point2, point3):
    p1, p2, p3 = point1[:2], point2[:2], point3[:2]
    p1 = np.append(p1, 1)
    p2 = np.append(p2, 1)
    p3 = np.append(p3, 1)
    a = np.array([p1, p2, p3])
    b = np.array([point1[2], point2[2], point3[2]])
    try:
        c = np.linalg.solve(a, b)
        c = np.round(c, 2)
        return c
    except np.linalg.LinAlgError:
        return None


def check_rotation(vec, rad):
    a = np.array(vec)
    b = np.array([[np.cos(rad), -np.sin(rad), 0], [np.sin(rad), np.cos(rad), 0], [0, 0, 1]])
    c = np.dot(b, a)
    c = np.round(c, 2)
    return c