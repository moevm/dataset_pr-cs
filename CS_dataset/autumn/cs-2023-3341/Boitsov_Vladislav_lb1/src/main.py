import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    if (point3[0]>=robot[0] and point1[0]<=robot[0] and point3[1]>= robot[1] and point1[1]<=robot[1]):
        return(True)
    else:
        return(False)

def check_collision(coefficients):
    collisions=[]
    matrix=[[y[x] for x in range(2)] for y in coefficients]
    for x in range(coefficients.shape[0]):
        for y in range(coefficients.shape[0]):
            if(x!=y and np.linalg.matrix_rank(np.array([matrix[x], matrix[y]]))==2):
                collisions.append((x, y))
    return(collisions)

def check_path(points_list):
    path_len=0
    points_num=len(points_list)
    points_list=np.array(points_list)
    for x in range(1, points_num):
        vector=points_list[x]-points_list[x-1]
        path_len+=np.linalg.norm(vector)
    return(round(path_len, 2))
