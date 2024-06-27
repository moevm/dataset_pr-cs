import numpy as np
import math

def check_crossroad(robot, point1, point2, point3, point4):
    x_sorted_points = sorted([point1, point2, point3, point4])
    y_sorted_points = sorted([point1, point2, point3, point4], key=lambda point: point[1])
    if x_sorted_points[0][0] <= robot[0] <= x_sorted_points[3][0] and y_sorted_points[0][1] <= robot[1] <= y_sorted_points[3][1]:
        return True
    else:
        return False

def check_collision(coefficients):
    num_coefficients = coefficients.shape[0]
    collisions = []
    for i in range(num_coefficients):
        for j in range(i + 1, num_coefficients):
            coeff_i = coefficients[i][:2]
            coeff_j = coefficients[j][:2]
            c_i = coefficients[i][2]
            c_j = coefficients[j][2]
            ab_matrix = np.array([coeff_i, coeff_j])
            c_vector = np.array([[c_i], [c_j]])
            abc_matrix = np.hstack((ab_matrix, c_vector))
            rank_ab = np.linalg.matrix_rank(ab_matrix)
            rank_abc = np.linalg.matrix_rank(abc_matrix)
            if rank_ab == rank_abc:
                collisions.append((i, j))
                collisions.append((j, i))
    collisions = sorted(collisions)
    return collisions

def check_path(points_list):
    total_distance = 0.0
    for i in range(1, len(points_list)):
        x1, y1 = points_list[i-1]
        x2, y2 = points_list[i]
        
        distance = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
        total_distance += distance
    return round(total_distance, 2)