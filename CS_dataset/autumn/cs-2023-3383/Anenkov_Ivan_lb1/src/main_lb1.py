import numpy as np
from numpy import linalg as LA

def check_crossroad(robot, point1, point2, point3, point4):
    return min(point1[0], point2[0])<=robot[0]<=max(point1[0], point2[0]) and min(point2[1], point3[1])<=robot[1]<=(max(point2[1],point3[1]))


def check_collision(coefficients):
    d=[]
    for i in range(len(coefficients)):
        for j in range(i+1, len(coefficients)):
            try:
                LA.solve(np.vstack([coefficients[i][:2], coefficients[j][:2]]), np.hstack([coefficients[i][2], coefficients[j][2]]))
                d.append((i, j))
                d.append((j, i))
            except:
                pass
    return sorted(d)



def check_path(points_list):
    path = 0
    for i in range(len(points_list)-1):
        path += np.sqrt((points_list[i+1][0]-points_list[i][0])**2+(points_list[i+1][1]-points_list[i][1])**2)
    return round(path, 2)
