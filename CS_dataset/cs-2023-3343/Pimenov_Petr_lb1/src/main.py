import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    rx, ry = robot
    p1x, p1y = point1
    p3x, p3y = point3
    return p3x >= rx >= p1x and p3y >= ry >= p1y


def check_collision(coefficients):
    result = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if i != j:
                matrix = np.array([coefficients[i][:2], coefficients[j][:2]])
                if np.linalg.matrix_rank(matrix) == 2:
                    result.append((i, j))
    return result


def check_path(points_list):
    path = 0
    for i in range(1, len(points_list)):
        x0, y0 = points_list[i - 1]
        x1, y1 = points_list[i]
        path += np.sqrt((x1 - x0) ** 2 + (y1 - y0) ** 2)
    return round(path, 2)
