import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    x_line_min, y_line_min = point1
    x_line_max, y_line_max = point3

    if x_line_min <= robot[0] <= x_line_max and y_line_min <= robot[1] <= y_line_max:
        return True
    else:
        return False


def check_collision(coefficients):
    result = []

    for index in range(len(coefficients)):
        numpay_arr = coefficients[index][0:2]

        for index_interior in range(len(coefficients)):
            numpay_arr_insert = coefficients[index_interior][0:2]
            matrix = np.array([numpay_arr, numpay_arr_insert])

            rank_of_matrix = np.linalg.matrix_rank(matrix)

            if rank_of_matrix == len(numpay_arr):
                result.append((index, index_interior))

    return result


def check_path(points_list):
    distance = 0

    for index in range(len(points_list) - 1):
        if index + 1 == len(points_list):
            break
        else:
            point_a = np.array(points_list[index])
            point_b = np.array(points_list[index + 1])
            distance += np.linalg.norm(point_a - point_b)

    return round(distance, 2)
