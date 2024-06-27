import numpy as np


def check_collision(bot1, bot2):
    matrix_coord = np.array(([bot1[0], bot1[1]], [bot2[0], bot2[1]]))
    c_array = np.array([-bot1[2], -bot2[2]])
    if np.linalg.det(matrix_coord) == 0:
        return None
    return tuple(np.round(np.linalg.solve(matrix_coord, c_array), 2))


def check_surface(point1, point2, point3):
    matrix_coord = np.array(([point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]))
    vec = np.array((point1[2], point2[2], point3[2]))
    rank = np.linalg.matrix_rank(matrix_coord)
    if np.linalg.det(matrix_coord) == 0:
        return None
    return np.round(np.linalg.solve(matrix_coord, vec), 2)


def check_rotation(vec, rad):
    x_coord = vec[0] * np.cos(rad) - vec[1] * np.sin(rad)
    y_coord = vec[0] * np.sin(rad) + vec[1] * np.cos(rad)
    return np.round([x_coord, y_coord, vec[2]], 2)
