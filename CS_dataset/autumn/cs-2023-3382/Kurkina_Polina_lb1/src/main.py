import cmath #для нахождения ранга матрицы
import numpy as np
import math as mt


def check_collision(bot1, bot2):
    left_matrix = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])  # левая часть матрицы
    right_matrix = np.array([-(bot1[2]), -(bot2[2])])  # правая часть матрицы
    if np.linalg.matrix_rank(left_matrix) == 2:
        ans = np.round(np.linalg.solve(left_matrix, right_matrix), 2)  # решение матрицы
    else:
        ans = None
    return tuple(ans)


def check_surface(point1, point2, point3):
    coef_s = np.array([[point1[0], point1[1], 1],
                       [point2[0], point2[1], 1],
                       [point3[0], point3[1], 1]],
                      )
    if np.linalg.matrix_rank(coef_s) == 3:
        values_s = np.array([point1[2], point2[2], point3[2]])
    else:
        return None
    res = np.round(np.linalg.solve(coef_s, values_s), 2)
    return res


def check_rotation(vec, rad):
    coef_r = np.array([
        [np.cos(rad), -np.sin(rad), 0],
        [np.sin(rad), np.cos(rad), 0],
        [0, 0, 1],
    ])
    return np.round(coef_r.dot(vec), 2)

