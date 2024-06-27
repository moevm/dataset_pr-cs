import numpy as np
import math


def check_crossroad(robot, point1, point2, point3, point4):
    if (point1[0] <= robot[0] <= point2[0]) and (point2[1] <= robot[1] <= point3[1]):
        return True
    else:
        return False


def check_collision(coefficients):
    add = []
    result = []
    num_bots = len(coefficients)
    for i in range(num_bots):
        add.append([0])
    coefficients = np.append(coefficients, [*add], axis= 1 )
    ready = np.hsplit(coefficients,2)
    first = ready[0]
    second = ready[1]
    second = np.delete(second,1,1)
    
    for i in range(num_bots):
        for j in range(i+1,num_bots):
            A = np.array([first[i],first[j]])
            B = np.array([second[i],second[j]])
            if np.linalg.matrix_rank(A)==2:
                result.append((i,j))
                result.append((j,i))

    return sorted(result)


def check_path(points_list):
    num = len(points_list)
    summ = 0
    for i in range(num-1):
        summ+=math.sqrt((points_list[i+1][0]-points_list[i][0])**2 + (points_list[i+1][1]-points_list[i][1])**2)
    summ = round(summ,2)
    return summ
