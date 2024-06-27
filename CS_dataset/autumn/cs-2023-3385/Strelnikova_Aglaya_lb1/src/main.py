import numpy as np
from numpy import linalg



def check_crossroad(robot, point1, point2, point3, point4):
    return robot[0] >= point1[0] and robot[0] <= point3[0] and robot[1] >= point2[1] and robot[1] <= point4[1]



def check_collision(coefficients):
    a = []
    for i in range(len(coefficients)):
        for j in range(i+1, len(coefficients)):
            M = np.array([coefficients[i][:2], coefficients[j][:2]])
            if (np.linalg.det(M) != 0):
                a.append((i, j))
                a.append((j, i))
    return sorted(a)



def check_path(points_list):
    b = 0
    for i in range(1, len(points_list)):
       b += ((points_list[i][0] - points_list[i - 1][0])**2 + (points_list[i][1] - points_list[i - 1][1])**2)**0.5
    return round(b, 2)