import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    return point1[0] <= robot[0] <= point3[0] and \
    point1[1] <= robot[1] <= point4[1]


def check_collision(coefficients):
    collisions = []
    for i in range(coefficients.shape[0]): 
        i_array = coefficients[i][0:2]

        for j in range(coefficients.shape[0]):
            if i != j:
                j_array = coefficients[j][0:2]
                matrix = np.array([i_array, j_array])

                if np.linalg.matrix_rank(matrix) == 2:
                    collisions.append((i, j))

    return collisions

    
def check_path(points_list):
    result = 0
    for i in range(len(points_list) - 1):
        x0, x1, y0, y1 = points_list[i][0], points_list[i+1][0], points_list[i][1], points_list[i+1][1]
        result += ( (x1 - x0) ** 2 + (y1 - y0) ** 2 ) ** 0.5
    return round(result, 2)
