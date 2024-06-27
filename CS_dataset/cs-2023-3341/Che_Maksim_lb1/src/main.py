import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    check_robot = False
    if point1[0] <= robot[0] <= point2[0] and point1[1] <= robot[1] <= point3[1]:
        return True
    else:
        return False
    pass


def check_collision(coefficients):
    collisions = []
    for i in range(coefficients.shape[0]):
        for j in range(coefficients.shape[0]):
            kof_1 = coefficients[i]
            kof_2 = coefficients[j]
            A = np.array([[kof_1[0], kof_1[1]], [kof_2[0], kof_2[1]]])
            B = np.array([kof_1[2], kof_2[2]])
            try:
                np.linalg.solve(A, B)
                collisions.append((i, j))
            except:
                pass
    return collisions


def check_path(points_list):
    points_list = np.array(points_list, dtype=float)
    path = 0
    for i in range(len(points_list) - 1):
        path += np.linalg.norm(points_list[i] - points_list[i + 1])
    path = round(path, 2)
    return path
    pass 
