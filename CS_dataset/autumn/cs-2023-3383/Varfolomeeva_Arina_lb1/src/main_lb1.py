import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    if (point1[0] < robot[0] < point2[0]) and (point1[1] < robot[1] < point4[1]):
        return True
    return False

def check_collision(coefficients):
    list_couples = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if i != j:
                A = np.array([coefficients[i][:2], coefficients[j][:2]])
                B = np.array([coefficients[i], coefficients[j]])
                if np.linalg.matrix_rank(A) >= 2 and np.linalg.matrix_rank(B) == np.linalg.matrix_rank(A):
                    list_couples.append((i, j))
    return list_couples

def check_path(points_list):
    points_list = np.array(points_list)
    length = 0
    for i in range(1, len(points_list)):
        length += np.linalg.norm(points_list[i] - points_list[i-1])
    length = round(length, 2)
    return length