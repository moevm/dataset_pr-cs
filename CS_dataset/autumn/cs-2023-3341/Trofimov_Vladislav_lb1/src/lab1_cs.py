import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    rectangle_length = [i for i in range(point1[0], point2[0] + 1)]
    rectangle_width = [i for i in range(point1[1], point4[1] + 1)]
    if robot[0] in rectangle_length and robot[1] in rectangle_width:
        return True
    else:
        return False

def check_collision(coefficients):
    matrix = []
    result = []
    x1,x2 = 0,1
    for i in range(len(coefficients)):
        y1 = -coefficients[i][0]*x1/coefficients[i][1] - coefficients[i][2]/coefficients[i][1]
        y2 = -coefficients[i][0]*x2/coefficients[i][1] - coefficients[i][2]/coefficients[i][1]
        vector = [x2-x1, y2-y1]
        matrix.append(vector)
    for j in range(len(matrix)):
        for k in range(len(matrix)):
            matrix_vectors = np.array([matrix[j], matrix[k]])
            if np.linalg.matrix_rank(matrix_vectors) != 1:
                result.append(tuple([j,k]))
    return result

def check_path(points_list):
    d = 0
    list_points_list = [list(arr) for arr in points_list]
    for i in range(len(list_points_list) - 1):
        x1,y1 = list_points_list[i][0], list_points_list[i][1]
        x2,y2 = list_points_list[i + 1][0], list_points_list[i + 1][1]
        d += ((x2 - x1)**2 + (y2 - y1)**2) ** 0.5
    return round(d,2)
