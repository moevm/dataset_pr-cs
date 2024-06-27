import numpy as np
import math

def check_crossroad(robot, point1, point2, point3, point4):
    x, y = robot
    x1, y1 = point1
    x2, y2 = point2
    x3, y3 =point3
    x4, y4 = point4
    if (x>x1 and x<x2) and (y>y1 and y<y4):
        return True
    else:
        return False


def check_collision(coefficients):
    N = len(coefficients)
    result = []
    for i in range(N):
        for j in range(i + 1, N):
            matriza = np.array([coefficients[i][0:2], coefficients[j][0:2]])
            lin = np.array([coefficients[i][2], coefficients[j][2]])
            rang = np.linalg.matrix_rank(matriza)
            if rang == 2:
                result.append((i, j))
                result.append((j, i))
    return sorted(result)

def check_path(points_list):
    distance = 0
    for i in range(1, len(points_list)):
        x1, y1 = points_list[i - 1]
        x2, y2 = points_list[i]
        rast = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
        distance += rast

    return round(distance, 2)
