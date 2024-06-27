import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    m_points=sorted([point1,point2,point3,point4])
    if robot[0]>=m_points[0][0] and robot[0]<=m_points[3][0] and robot[1]>=m_points[0][1] and robot[1]<=m_points[3][1]:
        return True
    else:
        return False


def check_collision(coefficients):
    pairs_robots=[]
    l=len(coefficients)
    for i  in range(l):
        for j in range(l):
            M=np.vstack((coefficients[i][:-1],coefficients[j][:-1]))
            rank=np.linalg.matrix_rank(M)
            if rank>=2:
                pairs_robots+=[(i,j)]
    return pairs_robots


def check_path(points_list):
    l=len(points_list)
    s=0
    for i in range(l-1):
        len_path=((points_list[i+1][0]-points_list[i][0])**2+(points_list[i+1][1]-points_list[i][1])**2)**0.5
        s+=len_path
    return round(s,2)
