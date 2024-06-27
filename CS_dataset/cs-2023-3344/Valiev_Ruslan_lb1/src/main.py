import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    xr, yr = robot
    x2, y2 = point2
    x4, y4 = point4
    if x4 <= xr <= x2 and y2 <= yr <= y4:
        return True
    return False


def check_collision(coefficients):
    anslist = []
    for n in range(len(coefficients)):
        for m in range(len(coefficients)):
            if n != m:
                c = np.array([coefficients[n][:2], coefficients[m][:2]])
                v = np.array([-coefficients[n][-1], -coefficients[m][-1]])
                try:
                    np.linalg.solve(c, v)
                    anslist.append((n, m))
                except:
                    pass
    return anslist


def check_path(points_list):
    pathlen = 0
    for i in range(len(points_list) - 1):
        pathlen += ((points_list[i + 1][0] - points_list[i][0]) ** 2 + (
                    points_list[i + 1][1] - points_list[i][1]) ** 2) ** 0.5
    pathlen = round(pathlen, 2)
    return pathlen