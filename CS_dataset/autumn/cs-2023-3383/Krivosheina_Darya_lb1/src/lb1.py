import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    x_r = robot[0]
    y_r = robot[1]
    x_p1 = point1[0]
    x_p2 = point2[0]
    y_p1 = point2[1]
    y_p2 = point3[1]
    if x_p1 <= x_r <= x_p2 and y_p1 <= y_r <= y_p2:
        return True
    else:
        return False
    pass


def check_collision(coefficients):
    k = list(coefficients)
    h = []
    for i in range(len(k)):
        for j in range(len(k)):
            if i == j:
                continue
            else:
                A = tuple(k[i][:2])
                B = tuple(k[j][:2])
                if np.linalg.matrix_rank((A, B)) == np.linalg.matrix_rank((k[i], k[j])):
                    b = (k[i][2], k[j][2])
                    try:
                        np.linalg.solve((A, B), b)
                    except LinAlgError:
                        pass
                    h.append((i, j))
    return h
    pass


def check_path(points_list):
    path = 0
    for i in range(len(points_list) - 1):
        path += ((points_list[i][0] - points_list[i + 1][0]) ** 2 + (points_list[i][1] - points_list[i + 1][1]) ** 2) ** 0.5
    path = round(path, 2)
    return path
    pass 
    
