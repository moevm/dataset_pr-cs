import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    f1 = (robot[0] >= point1[0]) and (robot[1] >= point1[1])
    f2 = (robot[0] <= point3[0]) and (robot[1] <= point3[1])
    return bool(f1 and f2)


def check_collision(coefficients):
    collisions = []
    for i in range(coefficients.shape[0]):
        for j in range(coefficients.shape[0]):
            if (i != j):
                Ri = coefficients[i]
                Rj = coefficients[j]
                if (Ri[0]*Rj[1] != Rj[0]*Ri[1] or 
                    Ri[0]*Rj[1] == Rj[0]*Ri[1] and Ri[2] == Rj[2]):
                    collisions.append( (i, j) )
    return collisions


def check_path(points_list):
    points_list = np.array(points_list, dtype=float)
    sm = 0
    for i in range(1, len(points_list)):
        sm += np.linalg.norm( points_list[i] - points_list[i-1] )
    return np.round(sm, 2)
