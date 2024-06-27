import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    x0, y0 = point1[0], point1[1]
    x1, y1 = point3[0], point3[1]
    x, y = robot[0], robot[1]
    if (x0 <= x <= x1) and (y0 <= y <= y1):
        return True
    else:
        return False


def check_collision(coefficients):
    n = len(coefficients)
    collisions = []
    for i in range(n):
        for j in range(n):
            matrix = np.vstack((coefficients[i][:2], coefficients[j][:2]))
            rank = np.linalg.matrix_rank(matrix)
            if rank > 1:
                collisions += [(i,j)]
    return collisions


def check_path(points_list):
    distance = 0
    for i in range(1, len(points_list)):
        x = points_list[i][0] - points_list[i-1][0]
        y = points_list[i][1] - points_list[i-1][1]
        vector = (x,y)
        distance += np.linalg.norm(vector)
    distance = round(distance, 2)
    return distance
