import numpy as np
import math

def check_crossroad(robot, point1, point2, point3, point4):
    if point1[0] <= robot[0] <= point3[0] and point1[1] <= robot[1] <= point3[1]:
        return True
    else:
        return False

def check_collision(coefficients):
    string = coefficients.shape[0]
    arr = []
    for i in range(string):
        for j in range(string):
            if (abs(i - j) >= 1):
                L = np.array((coefficients[i],coefficients[j]))
                if np.linalg.matrix_rank(L[:,:2]) >= 2:
                    duo = (i,j)
                    arr.append(duo)
    return arr

def check_path(points_list):
    res = 0
    for i in range(len(points_list)-1):
        res += math.sqrt((points_list[i][0] - points_list[i+1][0])**2 + (points_list[i][1] - points_list[i+1][1])**2)
    return round(res,2)