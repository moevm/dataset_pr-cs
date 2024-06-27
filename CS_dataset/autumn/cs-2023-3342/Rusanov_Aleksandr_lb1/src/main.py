import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    return all([point1[i] <= robot[i] <= point3[i] for i in (0, 1)])


def check_collision(coefficients):
    collisions = []
    for i in range(len(coefficients)):
        arr_i = coefficients[i][:2]
        for j in range(len(coefficients)):
            if i != j:

                arr_j = coefficients[j][:2]
                matrix = np.array([arr_i, arr_j])

                if np.linalg.matrix_rank(matrix) == 2:
                    collisions.append((i, j))

    return collisions


def check_path(points_list):
    path_length = 0
    for i in range(len(points_list) - 1):
        x0 = points_list[i][0]
        x1 = points_list[i + 1][0]
        y0 = points_list[i][1]
        y1 = points_list[i + 1][1]
        path_length += ((x1 - x0) ** 2 + (y1 - y0) ** 2) ** 0.5
    path_length = np.round(path_length, 2)
    return path_length
