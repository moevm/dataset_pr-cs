import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    if point1[0] <= robot[0] <= point2[0] and point1[1] <= robot[1] <= point4[1]:
        return True
    else:
        return False


def check_collision(coefficients):
    a = []
    coefficients = np.delete(coefficients, 2, axis=1)
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if i != j:
                mat_coef = np.array([coefficients[i], coefficients[j]])
                if np.linalg.det(mat_coef):
                    a.append((i, j))
    return a


def check_path(points_list):
    path = 0
    for i in range(len(points_list) - 1):
        f_vec = np.array(points_list[i])
        s_vec = np.array(points_list[i + 1])
        path += np.linalg.norm(s_vec - f_vec)
    return path.round(2)
