import numpy as np
import math


def check_collision(bot1, bot2):
    if np.linalg.matrix_rank(np.array([bot1, bot2])) != 2:
        return None
    im_point = np.linalg.solve(np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]]),
                               np.array([-bot1[2], -bot2[2]]))
    return tuple(np.around(im_point, 2))


def check_surface(point1, point2, point3):
    v_free = np.vstack([point1[2], point2[2], point3[2]])
    matrix_coeff = np.vstack([np.hstack([point1[0:2], 1]),
                              np.hstack([point2[0:2], 1]),
                              np.hstack([point3[0:2], 1])])
    matrix = np.hstack([matrix_coeff, v_free])
    if np.linalg.matrix_rank(matrix) != 3:
        return None
    v = np.linalg.solve(matrix_coeff, v_free)
    return np.around(*v.T, 2)


def check_rotation(vec, ang):
    cos = math.cos(ang)
    sin = math.sin(ang)
    rotation_matrix = np.array([[cos, -sin, 0], [sin, cos, 0], [0, 0, 1]])
    result = np.dot(rotation_matrix, vec)
    return np.around(result, 2)
