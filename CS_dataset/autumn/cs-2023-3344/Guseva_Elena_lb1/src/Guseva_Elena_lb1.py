import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    rx, ry=robot
    x=sorted([point1[0], point2[0], point3[0], point4[0]])
    y=sorted([point1[1], point2[1], point3[1], point4[1]])
    if x[0]<=rx<=x[3] and y[0]<=ry<=y[3]:
        return True
    else:
        return False


def check_collision(coefficients):
    crashed = []
    num_bots = len(coefficients)

    for i in range(num_bots):
        for j in range(num_bots):

            a1, b1, c1 = coefficients[i]
            a2, b2, c2 = coefficients[j]
            matrix = np.vstack(([a1, b1],[a2, b2]))

            if np.linalg.matrix_rank(matrix) >= 2:
                crashed.append((i, j))

    return crashed



def check_path(points_list):
    length = 0
    for i in range(len(points_list)-1):
        length += np.sqrt((points_list[i+1][0] - points_list[i][0])**2 + (points_list[i+1][1] - points_list[i][1])**2)
    return round(length, 2)