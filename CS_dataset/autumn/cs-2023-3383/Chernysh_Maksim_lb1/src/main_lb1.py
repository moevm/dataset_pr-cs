import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    return((point1[0]<=robot[0]<=point3[0])and(point1[1]<=robot[1]<=point3[1]))


def check_collision(coefficients):
    res = []
    for i in range(len(coefficients)):
        for j in range(i+1, len(coefficients)):
            matrix = np.array([coefficients[i][:2], coefficients[j][:2]])
            if np.linalg.det(matrix) != 0:
                res.append((i, j))
                res.append((j, i))
    return sorted(res)
                

def check_path(points_list):
    res = 0
    for i in range(len(points_list)-1):
        pos_1 = points_list[i]
        pos_2 = points_list[i+1]
        res += ((pos_2[0]-pos_1[0])**2+(pos_2[1]-pos_1[1])**2)**0.5
    return round(res,2)
