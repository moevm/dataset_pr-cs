import numpy as np
import math

from numpy.linalg import LinAlgError


def check_crossroad(robot, point1, point2, point3, point4):
    rx, ry = robot
    if (point1[0] <= rx and point1[1] <= ry) and (point2[0] >= rx and point2[1] <= ry) and (point3[0] >= rx and point3[1
    ]) and (point4[0] <= rx and point4[1] >= ry):
        return True
    else:
        return False


def check_collision(coefficients):
    array_for_first_arg = []
    if np.linalg.matrix_rank(coefficients) != 3:
        return array_for_first_arg
    array_for_second_arg = []
    result = []
    for i in coefficients:
        array_for_first_arg += [[i[0], i[1]]]
        array_for_second_arg += [i[2]]
    for i in range(len(array_for_second_arg)):
        for j in range(len(array_for_second_arg)):
            coeff_a = np.array([[array_for_first_arg[i][0], array_for_first_arg[i][1]], [array_for_first_arg[j][0],
                                                                                         array_for_first_arg[j][1]]])
            coeff_b = np.array([-array_for_second_arg[i], -array_for_second_arg[j]])
            try:
                np.linalg.solve(coeff_a, coeff_b)
                result += [(i, j)]
            except LinAlgError:
                pass
    return result


def check_path(points_list):
    summ = 0
    for i in range(len(points_list) - 1):
        summ += math.sqrt(
            abs(points_list[i][0] - points_list[i + 1][0]) ** 2 + abs(points_list[i][1] - points_list[i + 1][1
            ]) ** 2)
    return round(summ, 2)
