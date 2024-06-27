import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    coord = sorted([point1, point2, point3, point4])
    return (coord[0][0] <= robot[0] <= coord[-1][0]) and (coord[0][1] <= robot[1] <= coord[-1][1])


def check_collision(coefficients):
    result = []
    for i in range(len(coefficients)):
        k1 = -coefficients[i][0] / coefficients[i][1]
        b1 = -coefficients[i][2] / coefficients[i][1]
        for j in range(i + 1, len(coefficients)):
            k2 = -coefficients[j][0] / coefficients[j][1]
            b2 = -coefficients[j][2] / coefficients[j][1]
            if k1 != k2:
                result.extend([(i, j), (j, i)])
            else:
                if b1 == b2:
                    result.extend([(i, j), (j, i)])
    return sorted(result)


def check_path(points_list):
    result = 0
    for i in range(1, len(points_list)):
        result += np.linalg.norm((points_list[i][0] - points_list[i - 1][0], points_list[i][1] - points_list[i - 1][1]))
    return np.round(result, 2)