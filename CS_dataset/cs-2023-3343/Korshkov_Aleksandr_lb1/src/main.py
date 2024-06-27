import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    x0, x1, y0, y1 = point1[0], point3[0], point1[1], point3[1]
    if x0 <= robot[0] <= x1 and y0 <= robot[1] <= y1:
        return True
    return False

def check_collision(coefficients):
    pars = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if i != j:
                a1, b1 = coefficients[i][0], coefficients[i][1]
                a2, b2 = coefficients[j][0], coefficients[j][1]
                if (a2 * b1) - (a1 * b2) != 0:
                    pars.append(tuple([i ,j]))
    return pars


def check_path(points_list):
    path_len = 0
    for i in range(len(points_list) - 1):
        path_len += ((points_list[i + 1][0] - points_list[i][0]) ** 2
                     + (points_list[i + 1][1] - points_list[i][1]) ** 2) ** 0.5
    return round(path_len, 2)
