import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    return point1[0] <= robot[0] <= point2[0] and point1[1] <= robot[1] <= point4[1]


def check_collision(coefficients):
    list_conflict = []
    for i in range(len(coefficients)):
            for j in range(len(coefficients)):
                if i==j:
                    continue
                array = np.vstack((coefficients[i],coefficients[j]))
                array = array[:,:-1]
                if np.linalg.matrix_rank(array)==2:
                    list_conflict.append((i,j))
                    
    return list_conflict

                



def check_path(points_list):
     diff = np.diff(points_list,axis=0)
     lens = np.linalg.norm(diff,axis=1)
     len_path = round(sum(lens),2)

     return len_path

