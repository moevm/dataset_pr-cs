import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    if (point1[0] <= robot[0] <= point3[0]) and (point1[1] <= robot[1] <= point3[1]) :
        return True
    else:
        return False


def check_collision(coefficients):
    l = len(coefficients)
    res = []
    for i in range(l-1):
        for j in range(i+1,l):
            a = np.array([[coefficients[i][0], coefficients[i][1]],[coefficients[j][0], coefficients[j][1]]])
            b = np.array([coefficients[i],coefficients[j]])
            r1 = np.linalg.matrix_rank(a)
            r2 = np.linalg.matrix_rank(b)
            if r2 == r1:
                res.append((i,j))
                res.append((j,i))
    return sorted(res)


def check_path(points_list):
    S = 0
    for i in range(len(points_list)-1):
        x = points_list[i+1][0] - points_list[i][0]
        y = points_list[i+1][1] - points_list[i][1]
        dis = (x ** 2 + y ** 2) ** 0.5
        S += dis
    return round(S, 2)
