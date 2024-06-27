import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    return((robot[0] >= point1[0] and robot[0] <= point3[0]) and (robot[1] >= point1[1] and robot[1] <= point3[1]))


def check_collision(coefficients):
    matrix = np.delete(coefficients, 2, 1)
    res = []
    for i in range(len(matrix)):
        for j in range(i+1, len(matrix)):
            wmatrix = np.concatenate(([matrix[i]],[matrix[j]]), axis = 0)
            if np.linalg.det(wmatrix) != 0:
                res.append((i,j))
                res.append((j,i))
    return sorted(res)


def check_path(points_list):
    path = 0
    for i in range(len(points_list) - 1):
        vec = (points_list[i][0] - points_list[i+1][0], points_list[i][1] - points_list[i+1][1])
        path += np.linalg.norm(vec)
    path = round(path,2)
    return path
