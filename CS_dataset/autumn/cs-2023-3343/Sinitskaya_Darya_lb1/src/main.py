import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    if (((point1[0] or point4[0])<=robot[0]) and ((point3[0] or point2[0])>=robot[0])) and (((point1[1] or point2[1])<=robot[1])and((point3[1] or point4[1])>=robot[1])):
        return True
    else:
        return False


def check_collision(coefficients):
    list_pars=[]
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if i==j:
                continue
            x1,y1,z1 = coefficients[i]
            x2,y2,z2 = coefficients[j]
            M1 = np.array([[x1,x2],[y1,y2]])
            M2 = np.array([[z1,z2]])
            if np.linalg.matrix_rank(M1) <= np.linalg.matrix_rank(M2) or not np.any(M1) and not np.any(M2):
                continue
            list_pars.append(tuple([i,j]))
    return list_pars

def check_path(points_list):
    lenght=0
    for i in range(len(points_list)-1):
        x0=points_list[i][0]
        y0=points_list[i][1]
        x=points_list[i+1][0]
        y=points_list[i+1][1]
        from math import sqrt
        lenght+=sqrt((x0-x)**2+(y0-y)**2)
    return round(lenght,2)

