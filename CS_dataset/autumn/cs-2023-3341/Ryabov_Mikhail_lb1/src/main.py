import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    condition1 = (point1[0] <= robot[0]) and (point1[1] <= robot[1])
    condition2 = (point3[0] >= robot[0]) and (point3[1] >= robot[1])
    if condition1 and condition2:
        return True 
    return False


def check_collision(coefficients):
    total_collision = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if (-(coefficients[i][0] / coefficients[i][1])) != (-(coefficients[j][0] / coefficients[j][1])):
                total_collision.append((i, j))
    return total_collision


def check_path(points_list):
    length = 0
    for i in range(len(points_list)-1):
        x, y = points_list[i]
        x1, y1 = points_list[i+1]
        length += np.sqrt(((x1 - x)**2) + ((y1 - y)**2))
    return round(length, 2)

