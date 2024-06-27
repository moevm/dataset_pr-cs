import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    if point1[0]<=robot[0]<=point2[0] and point1[1]<=robot[1]<=point3[1]:
        return True
    else:
        return False
    
def check_collision(coefficients):
    n = len(coefficients)
    l = []
    for i in range(n-1):
        for j in range(i+1,n):
            A = np.array([[coefficients[i][0], coefficients[i][1]],[coefficients[j][0], coefficients[j][1]]])
            b = np.array([coefficients[i],coefficients[j]])
            rank1 = np.linalg.matrix_rank(A)
            rank2 = np.linalg.matrix_rank(b)
            if rank2 == rank1:
                l.append((i,j))
                l.append((j,i))
    return sorted(l)

def vec(a,b):
    return (a**2+b**2)**0.5

def check_path(points_list):
    sum = 0
    for i in range(len(points_list)-1):
        sum+=vec(points_list[i+1][0]-points_list[i][0],points_list[i+1][1]-points_list[i][1])
    return round(sum,2)

