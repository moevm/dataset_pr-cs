import numpy as np
from math import *
def check_collision(bot1, bot2):
    matrix1 = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    matrix2 = np.array([-bot1[2], -bot2[2]])
    if np.linalg.det(matrix1) == 0.0:
        return None
    intersection_point = tuple(np.round(np.linalg.solve(matrix1, matrix2),2))
    return intersection_point

def check_surface(point1, point2, point3):
    x1, y1, z1 = point1
    x2, y2, z2 = point2
    x3, y3, z3 = point3
    matrix_b = np.array([[x1, y1, 1], [x2, y2, 1], [x3, y3, 1]])
    free_vector = np.array([z1, z2, z3])
    if np.linalg.det(matrix_b) == 0.0:
        return None
    ans = np.round(np.linalg.solve(matrix_b, free_vector),2)
    return ans

def check_rotation(vec, rad):
    matrix_rotation = np.array([[cos(rad), sin(rad), 0],
                                [-sin(rad), cos(rad), 0],
                                [0, 0, 1]])
    res = np.round(np.matmul(vec, matrix_rotation),2)
    return res
