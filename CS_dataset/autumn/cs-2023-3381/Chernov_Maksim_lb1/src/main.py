import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    if (point1[0] <= robot[0] <= point3[0]) and (point1[1] <= robot[1] <= point3[1]):
        return True
    else:
        return False


def check_collision(coefficients):
    fl_matrix = np.delete(coefficients, 2, 1)
    out = []
    for i in range(len(fl_matrix)):
        for j in range(i + 1, len(fl_matrix)):
            matrix = np.concatenate(([fl_matrix[i]], [fl_matrix[j]]), axis=0)
            if np.linalg.det(matrix) != 0:
                out.append((i, j))
                out.append((j, i))
    return sorted(out)


def check_path(points_list):
    path = 0
    for i in range(len(points_list) - 1):
        vector = (points_list[i][0] - points_list[i + 1][0], points_list[i][1] - points_list[i + 1][1])
        path += np.linalg.norm(vector)
    return round(path, 2)