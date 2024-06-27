import numpy as np
from math import *
def check_crossroad(robot, point1, point2, point3, point4):
    xrob,yrob = robot
    if (point1[0] <= xrob <= point2[0]) and (point1[1] <= yrob <= point3[1]):
        return('True')
    else:
        return('False')

def check_collision(coefficients):
    cfs = coefficients
    ans = []
    for i in range(len(cfs)):
        for j in range(i,len(cfs)):
            A = [[cfs[i][0],cfs[i][1]],[cfs[j][0],cfs[j][1]]]
            if np.linalg.det(A)!= 0:
                ans.append((i,j))
                ans.append((j,i))
    return sorted(ans)

def check_path(points_list):
    x0,y0 = points_list[0]
    trace = 0
    for i in range(1,len(points_list)):
        x = points_list[i][0]
        y = points_list[i][1]
        trace += np.linalg.norm([x-x0,y-y0])
        x0,y0 = x,y
    return round(trace,2)
