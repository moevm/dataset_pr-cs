import numpy as np
def check_crossroad(robot, point1, point2, point3, point4):
    if (robot[0] >= point1[0]) and (robot[1] >= point1[1]) and (robot[0] <= point3[0]) and (robot[1] <= point3[1]):
        return True
    return False
def check_collision(coefficients):
    crossed = []
    for i in range(len(coefficients)):
        for j in range(i + 1, len(coefficients)):
            matrix_ab = np.array([coefficients[i][:2], coefficients[j][:2]])
            matrix_c = np.array([[coefficients[i][2]], [coefficients[j][2]]])
            matrix_abc = np.hstack((matrix_ab, matrix_c))
            if (np.linalg.matrix_rank(matrix_ab)) == (np.linalg.matrix_rank(matrix_abc)):
                crossed.append((i, j))
                crossed.append((j, i))
    return sorted(crossed)
def check_path(points_list):
    len_way = 0
    for i in range(len(points_list) - 1):
        vector = (points_list[i + 1][0] - points_list[i][0], points_list[i + 1][1] - points_list[i][1])
        len_way += np.linalg.norm(vector)
    return round(len_way, 2)