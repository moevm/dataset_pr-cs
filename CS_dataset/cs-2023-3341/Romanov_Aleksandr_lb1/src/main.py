import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    x1, x2 = point1[0], point3[0]
    y1, y2 = point1[1], point3[1]
    if (x1 <= robot[0] <= x2) and (y1 <= robot[1] <= y2):
        return True
    return False
    pass


def check_collision(coefficients):
    res = []
    for i in range(0, len(coefficients) - 1):
        for j in range(i + 1, len(coefficients)):
            syst = np.array((coefficients[i], coefficients[j]))
            if np.linalg.matrix_rank(syst[:, :-1]) == np.linalg.matrix_rank(syst) == 2:
                res.append((i, j))
                res.append((j, i))
            else:
                continue
    res.sort()
    return res
    pass


def check_path(points_list):
    points_list = np.array(points_list)
    res = 0
    for i in range(1, len(points_list)):
        vec = np.array([points_list[i, 0] - points_list[i - 1, 0], points_list[i, 1] - points_list[i - 1, 1]])
        res += np.linalg.norm(vec)
    res = round(res, 2)
    return res

