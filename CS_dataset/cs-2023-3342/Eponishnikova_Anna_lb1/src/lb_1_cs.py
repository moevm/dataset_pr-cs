import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    if point1[0] <= robot[0] <= point3[0] and point1[1] <= robot[1] <= point3[1]:
        return True
    else:
        return False


def check_collision(coefficients):
    answer = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            matrix_i = coefficients[i][:2]
            matrix_j = coefficients[j][:2]
            matrix = np.vstack((coefficients[i][:2], coefficients[j][:2]))
            if (np.linalg.matrix_rank(matrix) == len(matrix_i)):
                answer.append((i,j))
    return answer

def check_path(points_list):
    path = 0
    for i in range(len(points_list) - 1):
        vector1 = np.array(points_list[i])
        vector2 = np.array(points_list[i+1])
        path += np.linalg.norm(vector2 - vector1)
    return round(path,2)
    


    
