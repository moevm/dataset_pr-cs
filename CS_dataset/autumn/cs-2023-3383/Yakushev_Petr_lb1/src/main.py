import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    xgmi=min(point1[0],point2[0],point3[0],point4[0])
    ygmi=min(point1[1],point2[1],point3[1],point4[1])
    xgma=max(point1[0],point2[0],point3[0],point4[0])
    ygma=max(point1[1],point2[1],point3[1],point4[1])
    if robot[0]<=xgma and robot[0]>=xgmi:
        if robot[1]>=ygmi and ygma>=robot[1]:
            return True
        else:
            return False
    else:
        return False


def check_collision(coefficients):
    kolvo=len(coefficients)
    bum = []
    for i in range(kolvo):
        for j in range(i+1, kolvo):
            mas = [[coefficients[i][0], coefficients[i][1]],[coefficients[j][0], coefficients[j][1]]]
            if np.linalg.matrix_rank(mas)==2:
                bum.append((i, j))
                bum.append((j, i))
    bum.sort()
    return bum


def check_path(points_list):
    points_list=list(map(list, points_list))
    dif = np.diff(points_list, axis=0)
    vektors = np.linalg.norm(dif, axis=1)
    ras = np.sum(vektors)
    return round(ras,2)
