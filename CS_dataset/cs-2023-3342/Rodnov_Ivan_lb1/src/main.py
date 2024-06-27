import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    return point1[0] <= robot[0] <= point3[0] and point2[1] <= robot[1] <= point4[1]


def check_collision(coefficients):
    answer = []
    for i in range(coefficients.shape[0]):
        for j in range(coefficients.shape[0]):
            if i != j:
                arri = coefficients[i][0:2]
                arrj = coefficients[j][0:2]
                Mat = np.array([arri, arrj])
                if np.linalg.matrix_rank(Mat) == 2:
                    answer.append((i, j))
    return answer


def check_path(points_list):
    a = 0
    for i in range(len(points_list)-1):
        a += np.sqrt(((points_list[i+1][0]-points_list[i][0])**2) + ((points_list[i+1][1]-points_list[i][1])**2))
    return np.around(a, 2)
