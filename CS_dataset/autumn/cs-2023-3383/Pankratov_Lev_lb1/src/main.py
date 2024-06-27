import numpy as np

def check_collision(bot1, bot2):
    a = np.array([bot1[:2], bot2[:2]])
    b = np.array([-bot1[2], -bot2[2]])
    if np.linalg.matrix_rank(a) == 2:
        return tuple(np.round(np.linalg.solve(a, b), 2))
    pass


def check_surface(point1, point2, point3):
    a = np.concatenate((np.array([point1[:2], point2[:2], point3[:2]]), np.array([[1],[1],[1]])), axis=1)
    z = np.array([point1[2], point2[2], point3[2]])
    if np.linalg.matrix_rank(a) == 3:
        return np.round(np.linalg.solve(a,z), 2)
    pass


def check_rotation(vec, rad):
    a = np.array([[np.cos(rad), -np.sin(rad), 0], [np.sin(rad), np.cos(rad), 0], [0, 0, 1]])
    return np.round(a @ vec, 2)

