import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    return (point1[0]<=robot[0]<=point2[0]) and (point1[1]<=robot[1]<=point3[1])


def check_collision(coefficients):
    collisions = []
    for i in range(len(coefficients)):
        arr = coefficients[i][0:2]
        for j in range(len(coefficients)):
            arr_insert = coefficients[j][0:2]
            matrix = np.array([arr, arr_insert])
            rank_of_matrix = np.linalg.matrix_rank(matrix)
            if rank_of_matrix == len(arr):
                collisions.append((i, j))
    return collisions


def check_path(points_list):
    result = 0
    for i in range(len(points_list)-1):
        x0, x1 = points_list[i][0], points_list[i+1][0]
        y0, y1 = points_list[i][1], points_list[i+1][1]
        result += ((x1 - x0) ** 2 + (y1 - y0) ** 2)**0.5
    return round(result, 2)
