import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    if point1[0] <= robot[0] <= point3[0] and point2[1] <= robot[1] <= point4[1]:
        return True
    else:
        return False


def check_collision(coefficients):
    res=[]
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            st1=coefficients[i]
            st2=coefficients[j]
            mat = np.vstack((st1[0:2], st2[0:2]))
            if np.linalg.matrix_rank(mat) >= 2:
                res.append((i, j))
    return res


def check_path(points_list):
    res=0
    for i in range(len(points_list)-1):
        x0=points_list[i]
        x1=points_list[i+1]
        s=((x1[0]-x0[0])**2+(x1[1]-x0[1])**2)**0.5
        res+=s
    return round(res,2)
