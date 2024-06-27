import numpy as np
from math import *

def check_crossroad(robot, point1, point2, point3, point4):
    if (robot[0]>=point1[0] and robot[0]<=point2[0]) and (robot[1]>=point1[1] and robot[1] <= point4[1]):
        return True
    else:
        return False
    pass

def check_collision(coefficients):
    peresech = []
    for i in range(len(coefficients)):
        for j in range(i,len(coefficients)):
            mat = [[coefficients[i][0], coefficients[i][1]], [coefficients[j][0], coefficients[j][1]]]
            if np.linalg.matrix_rank(mat)==2:
                peresech.append((i, j))
                peresech.append((j, i))
    peresech.sort()
    return peresech
    
    pass


def check_path(points_list):
    a,b = points_list[0]
    put = 0
    for i in range(1,len(points_list)):
        x = points_list[i][0]
        y = points_list[i][1]
        put += sqrt((x-a)**2 + (y-b)**2)
        a,b = x,y
    return round(put,2)
    pass
