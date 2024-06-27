import numpy as np


def check_collision(bot1, bot2):
    a1, b1, c1 = bot1
    a2, b2, c2 = bot2
    det = a1 * b2 - a2 * b1
    if det != 0:
        x = (c1 * b2 - c2 * b1) / det
        y = (a1 * c2 - a2 * c1) / det
        x = round(x, 2)
        y = round(y, 2)
        return (-x, -y)
    else:
        return None


def check_surface(point1, point2, point3):
    x1, y1, z1 = point1
    x2, y2, z2 = point2
    x3, y3, z3 = point3
    xx = x2 - x1
    yy = y2 - y1
    zz = z2 - z1
    xx1 = x3 - x2
    yy1 = y3 - y2
    zz1 = z3 - z2
    if yy1 * xx - yy * xx1 == 0:
        return None
    if xx == 0:
        return None
    b = (zz1 * xx - zz * xx1) / (yy1 * xx - yy * xx1)
    a = (zz - b * yy) / xx
    c = z1 - a * x1 - b * y1
    a = round(a, 2)
    b = round(b, 2)
    c = round(c, 2)
    k = np.array([a, b, c])
    return (k)

def check_rotation(vec, rad):
    mx = [[np.cos(rad), -np.sin(rad), 0],
                                 [np.sin(rad), np.cos(rad), 0],
                                 [0, 0, 1]]

    mx = np.dot(mx, vec)
    a, b, c = mx
    a = round(a, 2)
    b = round(b, 2)
    c = round(c, 2)
    k = np.array([a, b, c])
    return (k)
