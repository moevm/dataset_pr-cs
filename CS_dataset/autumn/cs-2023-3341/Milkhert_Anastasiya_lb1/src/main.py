import numpy as np
import math


def check_crossroad(robot, point1, point2, point3, point4):
    if (robot[0] >= point1[0] and robot[0] >= point4[0] and robot[0] <= point2[0] and robot[0] <= point3[0]) and (
            robot[1] >= point1[1] and robot[1] >= point2[1] and robot[1] <= point3[1] and robot[1] <= point4[1]):
        return True
    return False


def check_collision(coefficients):
    matrix = [[ell for ell in el]for el in coefficients]
    answer = []
    length = coefficients.shape[0]
    for i in range(length):
        coefficient_a_b_1 = np.array(matrix[i][:2])
        for j in range(length):
            if i != j:
                coefficient_a_b_2 = np.array(matrix[j][:2])
                if np.linalg.matrix_rank([coefficient_a_b_1, coefficient_a_b_2]) >= 2:
                    answer.append((i, j))
    return answer


def check_path(points_list):
    answer = 0
    for i in range(1, len(points_list)):
        vector = [points_list[i][0] - points_list[i-1][0], points_list[i][1] - points_list[i-1][1]]
        answer += math.sqrt((vector[0]**2) + (vector[1]**2))
    return round(answer, 2)


