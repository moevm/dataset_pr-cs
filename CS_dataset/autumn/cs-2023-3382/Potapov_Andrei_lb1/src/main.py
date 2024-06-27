import numpy as np


def check_collision(bot1, bot2):
    a = np.array([bot1[:2], bot2[:2]])
    b = np.array([-bot1[2], -bot2[2]])
    if np.linalg.matrix_rank(a) == 2:
        return tuple(np.linalg.solve(a, b).round(2))
    else:
        return None


def check_surface(point1, point2, point3):
    a = np.vstack((point1, point2, point3))
    for i in range(3):
        a[i][2] = 1
    b = np.array([point1[2], point2[2], point3[2]])
    if np.linalg.matrix_rank(a) == 3:
        return np.linalg.solve(a, b).round(2)
    else:
        return None


def check_rotation(vec, rad):
    np_cords = np.array(vec)
    a = np.array([[np.cos(rad), -np.sin(rad), 0],
                  [np.sin(rad), np.cos(rad), 0],
                  [0, 0, 1],
                  ])
    return np.dot(a, np_cords).round(2)

