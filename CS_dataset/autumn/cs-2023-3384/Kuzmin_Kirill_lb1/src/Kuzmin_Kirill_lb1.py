import numpy as np
import math


def check_crossroad(robot, point1, point2, point3, point4):
    x = robot[0]
    y = robot[1]
    if x >= point1[0] and y >= point1[1] and x <= point3[0] and y <= point3[1]:

        return True
    else:

        return False


def check_collision(coefficients):
    s = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)): 
            if i != j:
                n_array = np.array([[coefficients[i][0], coefficients[i][1]], [coefficients[j][0], coefficients[j][1]]])
                det = np.linalg.det(n_array)
                if det != 0:
                    d = tuple([i, j])
                    s += [d]

    return s


def check_path(points_list):
    s = 0
    for i in range(len(points_list)-1):
        d = (abs(points_list[i+1][0]-points_list[i][0])**2+abs(points_list[i+1][1]-points_list[i][1])**2)
        s += d**0.5
    return round(s, 2)

