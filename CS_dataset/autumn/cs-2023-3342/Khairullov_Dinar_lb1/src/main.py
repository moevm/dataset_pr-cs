import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    coords_x = []
    coords_y = []
    coords_list = [point1, point2, point3, point4]
    for couple in coords_list:
        coords_x.append(couple[0])
        coords_y.append(couple[1])
    bool_sen = min(coords_x) <= robot[0] and robot[0] <= max(coords_x) and min(coords_y) <= robot[1] and robot[1] <= max(coords_y)
    if bool_sen:
        return True
    else:
        return False

def check_collision(coefficients):
    res = []
    for i1 in range(0,len(coefficients)):
        for i2 in range(0,len(coefficients)):
            check_matrix = np.array((coefficients[i1][0:2],coefficients[i2][0:2]))
            if len(check_matrix) <= np.linalg.matrix_rank(check_matrix) :
                couple = (i1,i2)
                res.append(couple)
    return res

def check_path(points_list):
    path = 0
    for i in range(1,len(points_list)):
        x_diff = points_list[i][0] - points_list[i-1][0]
        y_diff = points_list[i][1] - points_list[i-1][1]
        vec = np.array((x_diff,y_diff))
        length = np.linalg.norm(vec)
        path += length
    return round(path,2)
