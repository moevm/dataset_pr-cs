import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    if point1[0] <= robot[0] <= point3[0]:
        if point1[1] <= robot[1] <= point3[1]:
            return True
    return False


def check_collision(coefficients):
    answer = []
    for ind_first in range(len(coefficients)):
        for ind_second in range(len(coefficients)):
            if ind_first != ind_second:
                if not (
                    coefficients[ind_first][0] / coefficients[ind_first][1]
                    == coefficients[ind_second][0] / coefficients[ind_second][1]
                ):
                    answer.append((ind_first, ind_second))
    return answer


def check_path(points_list):
    answer = 0
    S = lambda x, y: np.sqrt((x[0] - y[0]) ** 2 + (x[1] - y[1]) ** 2)
    start = points_list.pop(0)
    for points in points_list:
        answer += S(start, points)
        start = points
    return np.round(answer, 2)
