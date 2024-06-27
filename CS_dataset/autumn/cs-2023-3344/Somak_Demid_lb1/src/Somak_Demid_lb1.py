import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    if point2[0] >= robot[0] >= point1[0] and point4[1] >= robot[1] >= point1[1]:
        return True
    else:
        return False


def check_collision(coefficients):
    result = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            str1 = coefficients[i]
            str2 = coefficients[j]
            matr = np.vstack((str1[0:2], str2[0:2]))
            if np.linalg.matrix_rank(matr) >= 2:
                result.append((i, j))
    return result


def check_path(points_list):
    lenght = 0
    for i in range(0,len(points_list)-1):
        point1, point2 = points_list[i], points_list[i+1]
        x1, y1 = point1[0], point1[1]
        x2, y2 = point2[0], point2[1]
        vec = np.array([x2-x1, y2-y1])
        lenght += np.linalg.norm(vec)
    lenght = round(lenght, 2)
    return lenght