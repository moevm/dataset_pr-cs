import numpy as np


def check_collision(bot1, bot2):
    a1, b1, c1 = bot1
    a2, b2, c2 = bot2
    coefficients = np.array([[a1,b1], [a2,b2]])
    result = np.array((-c1, -c2))
    rank = np.linalg.matrix_rank(coefficients)
    if rank >= 2:
        a, b = np.linalg.solve(coefficients, result)
        return (round(a,2), round(b,2))
    return None

def check_surface(point1, point2, point3):
    result = np.array((point1[2], point2[2], point3[2]))
    point1[2] = point2[2] = point3[2] = 1
    coefficients = np.array((point1, point2, point3))
    if np.linalg.matrix_rank(coefficients) >= 3:
        a, b, c = np.linalg.solve(coefficients, result)
        return np.array([round(a,2), round(b,2), round(c,2)])
    return None


def check_rotation(vec, rad):
    reversal = np.array(((np.cos(rad), -np.sin(rad), 0),
                         (np.sin(rad), np.cos(rad), 0),
                         (0, 0, 1)))
    a, b, c = np.dot(reversal, vec)
    return np.array([round(a, 2), round(b, 2), round(c, 2)])