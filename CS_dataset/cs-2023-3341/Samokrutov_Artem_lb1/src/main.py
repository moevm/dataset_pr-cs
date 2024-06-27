import numpy as np

def solution_exists(matrix_a, column_vector_b):
    ext_matrix_a = np.hstack((matrix_a, [[x] for x in column_vector_b]))
    if np.linalg.matrix_rank(matrix_a) == np.linalg.matrix_rank(ext_matrix_a) and np.linalg.det(matrix_a) != 0:
        return True
    else:
        return False

def check_collision(bot1, bot2):
    a1, b1, c1 = bot1
    a2, b2, c2 = bot2

    matrix_a = np.array([[a1, b1],
                         [a2, b2]])
    column_b = np.array([-c1, -c2])

    if solution_exists(matrix_a, column_b):
        solution_matrix = np.linalg.solve(matrix_a, column_b)
        return tuple(np.round(solution_matrix, 2))
    else:
        return None


def check_surface(point1, point2, point3):
    x1, y1, z1 = point1
    x2, y2, z2 = point2
    x3, y3, z3 = point3

    matrix_a = np.array(([x1, y1, 1],
                         [x2, y2, 1],
                         [x3, y3, 1]))
    matrix_b = np.array([z1, z2, z3])

    if solution_exists(matrix_a, matrix_b):
        solution_matrix = np.linalg.solve(matrix_a, matrix_b)
        return np.round(solution_matrix, 2)
    else:
        return None


def check_rotation(vec, rad):
    rotation_matrix = np.array([[np.cos(rad), -(np.sin(rad)), 0],
                                [np.sin(rad), np.cos(rad), 0],
                                [0, 0, 1]])
    vec_after_rotation = np.dot(rotation_matrix, vec)
    return np.round(vec_after_rotation, 2)
