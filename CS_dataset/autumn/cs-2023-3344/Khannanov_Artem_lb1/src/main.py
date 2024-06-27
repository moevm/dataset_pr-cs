import numpy as np


def is_one_solution(system, extended):
    if np.linalg.matrix_rank(system) == np.linalg.matrix_rank(extended):
        return np.linalg.matrix_rank(system)
    return False


def check_collision(bot1, bot2):
    # матрица системы:
    system_matrix = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    # матрица свободных членов:
    free_members_matrix = np.array([bot1[2] * -1, bot2[2] * -1])
    # расширенная матрица системы:
    extended_matrix = np.array([[bot1[0], bot1[1], bot1[2] * -1], [bot2[0], bot2[1], bot2[2] * -1]])

    # проверка на наличие решения и возвращение результата
    if is_one_solution(system_matrix, extended_matrix) >= 2:
        x, y = np.linalg.solve(system_matrix, free_members_matrix)
        return round(x, 2), round(y, 2)
    return None


def check_surface(point1, point2, point3):
    # матрица системы
    system_matrix = np.array([[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]])
    # матрица свободных членов
    free_members_matrix = np.array([[point1[2]], [point2[2]], [point3[2]]])
    # расширенная матрица
    extended_matrix = np.hstack((system_matrix, free_members_matrix))

    # проверка на наличие решения и возвращение результата
    if is_one_solution(system_matrix, extended_matrix) >= 3:
        coefficient_matrix = np.linalg.solve(system_matrix, free_members_matrix)
        return np.round(np.transpose(coefficient_matrix)[0], 2)
    return None


def check_rotation(vec, rad):
    # матрица поворота
    rotation_matrix = np.transpose(np.array([[np.cos(rad), np.sin(rad) * -1], [np.sin(rad), np.cos(rad)]]))
    # изменение координат
    x, y, z = vec
    matrix_for_changing_coordinates = np.array([[x], [y]])
    rotated_matrix = np.linalg.solve(rotation_matrix, matrix_for_changing_coordinates)
    rotated_matrix = np.append(np.transpose(rotated_matrix), z)
    return np.round(np.transpose(rotated_matrix), 2)