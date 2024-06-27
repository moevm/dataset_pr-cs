import numpy as np
import math as m


def check_crossroad(robot, point1, point2, point3, point4):
    points = [point1,point2,point3,point4]
    points = sorted(points)

    return (((robot[0] >= points[0][0]) and (robot[1] >= points[0][1])) and ((robot[0] <= points[3][0]) and (robot[1] <= points[3][1])))

def check_collision(coefficients):
    collisions = []

    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if (i != j):
                coefficients_i = coefficients[i]
                coefficients_j = coefficients[j]

                vector_i = np.array( [1, (-coefficients_i[0] - coefficients_i[2]) / coefficients_i[1]] ) - np.array([0, -coefficients_i[2] / coefficients_i[1]])
                vector_j = np.array( [1, (-coefficients_j[0] - coefficients_j[2]) / coefficients_j[1]] ) - np.array([0, -coefficients_j[2] / coefficients_j[1]])

                matrix = np.array([vector_i, vector_j])
                matrix_rank = np.linalg.matrix_rank(matrix)

                if (matrix_rank == 2):
                    collisions.append((i, j))

    return collisions

def check_path(points_list):
    path_length = 0

    for i in range(len(points_list) - 1):
        start_point = points_list[i]
        end_point = points_list[i + 1]
        path_length += m.sqrt(((end_point[0] - start_point[0]) ** 2) + ((end_point[1] - start_point[1]) ** 2))  

    path_length = round(path_length, 2)
    return path_length
