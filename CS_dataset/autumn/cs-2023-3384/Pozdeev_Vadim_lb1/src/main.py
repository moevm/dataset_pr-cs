from math import sqrt
import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    xs = (point1[0], point3[0])
    ys = (point2[1], point4[1])
    if (xs[0] <= robot[0] <= xs[1]) and (ys[0] <= robot[1] <= ys[1]):
        return True
    return False


def check_collision(coefficients):
    res = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if i != j:
                if np.linalg.matrix_rank(np.vstack((coefficients[i][:2], coefficients[j][:2]))) == 2:
                    res.append((i, j))
    return res


def check_path(points_list):
    s = 0
    for i in range(len(points_list)-1):
        x1 = points_list[i]
        x2 = points_list[i+1]
        s += sqrt( (x1[0]-x2[0])**2+ (x1[1]-x2[1])**2 )
    return round(s, 2)

    
