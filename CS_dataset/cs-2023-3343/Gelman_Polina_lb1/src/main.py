import numpy as np
from math import *
def check_collision(bot1, bot2):
    # формируем систему линейных уравнений в виде Ax = B,
    # где А - матрица коэфф. при переменных, х - матрица-столбец переменных,
    # В - матрица-столбец свободных членов
    A = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    B = np.array([-bot1[2], -bot2[2]])
    if np.linalg.det(A) == 0.0: # если определитель матрицы равен нулю, то есть линейная зависимость => у системы нет решений
        return None
    else:
        intersection_point = tuple(np.round(np.linalg.solve(A, B),2))
        return intersection_point



def check_surface(point1, point2, point3):
    x1, y1, z1 = point1
    x2, y2, z2 = point2
    x3, y3, z3 = point3
    matrix_c = np.array([[x1, y1, 1], [x2, y2, 1], [x3, y3, 1]]) # матрица коэффициентов
    free_vector = np.array([z1, z2, z3]) # вектор свободных членов

    if np.linalg.det(matrix_c) == 0.0:
        return None
    else:
        answer = np.round(np.linalg.solve(matrix_c, free_vector),2)

        return answer


def check_rotation(vec, rad):
    matrix_rotation = np.array([[cos(rad), sin(rad), 0], [-sin(rad), cos(rad), 0], [0, 0, 1]]) # создаем матрицу поворота вокруг оси z
    result = np.round(np.matmul(vec, matrix_rotation),2) # матричное умножение
    return result
