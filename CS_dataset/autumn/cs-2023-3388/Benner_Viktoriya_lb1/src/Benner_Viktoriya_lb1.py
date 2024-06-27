import numpy as np

def check_collision(bot1, bot2):
    a = np.array([
        [bot1[0], bot1[1]],
        [bot2[0], bot2[1]]]
    )
    if np.linalg.matrix_rank(a) == 2:
        vec = np.array([-bot1[2], -bot2[2]])
        return tuple(np.linalg.solve(a, vec).round(2))
    else:
        return None

def check_surface(point1, point2, point3):
    a = np.vstack((point1, point2, point3))
    a[0][2] = 1
    a[1][2] = 1
    a[2][2] = 1
    b = np.array([point1[2], point2[2], point3[2]])
    if np.linalg.matrix_rank(a) == 3:
        rez = np.linalg.solve(a, b)
        p = np.round(rez, 2)
        return p
    else:
        return None

def check_rotation(vec, rad):
    a = np.array([
        [np.cos(rad), -np.sin(rad), 0],
        [np.sin(rad), np.cos(rad), 0],
        [0, 0, 1],
    ])
    return np.round(a.dot(vec), 2)
