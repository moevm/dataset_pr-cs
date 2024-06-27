import numpy as np
from math import sin, cos


def check_collision(b1, b2):
    A, B = np.vstack((b1[:-1], b2[:-1])), np.array([-b1[-1], -b2[-1]])
    if np.linalg.matrix_rank(np.vstack((b1, b2))) != 2 or np.linalg.matrix_rank(A) != 2:
        return None
    collision_point = np.linalg.solve(A, B)
    return tuple(round(i, 2) for i in collision_point)


def check_surface(p1, p2, p3):
    a1, a2, a3 = p1[:-1], p2[:-1], p3[:-1]
    a1 = np.append(a1, 1)
    a2 = np.append(a2, 1)
    a3 = np.append(a3, 1)
    A, B = np.vstack((a1, a2, a3)), np.array([p1[-1], p2[-1], p3[-1]])
    if any((np.linalg.matrix_rank(np.vstack((np.append(a1, B[0]),
                                             np.append(a2, B[1]),
                                             np.append(a3, B[2])))) != 3,
            np.linalg.matrix_rank(A) != 3)):
        return None
    surface = np.linalg.solve(A, B)
    return np.array([round(i, 2) for i in surface])


def check_rotation(coords, angle):
    rotation_matrix = np.array([[cos(angle), -sin(angle), 0],
                                [sin(angle), cos(angle), 0],
                                [0, 0, 1]])
    result_coords = np.dot(rotation_matrix, coords)
    return np.array([round(i, 2) for i in result_coords])
