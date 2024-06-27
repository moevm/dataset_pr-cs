import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    return (point1[0] <= robot[0] <= point3[0]) and (point1[1] <= robot[1] <= point3[1])


def check_collision(coefs):
    Amatrix = np.delete(coefs, 2, 1)
    out = []
    for i in range(Amatrix.shape[0]):
        for j in range(Amatrix.shape[0]):
            linear_system = np.vstack([Amatrix[i], Amatrix[j]])
            if np.linalg.det(linear_system) != 0:
                out.append((i, j))
    return sorted(out)


def check_path(path):
    S = 0
    for i in range(len(path) - 1):
        S += np.sqrt((path[i][0] - path[i + 1][0])**2 + (path[i][1] - path[i + 1][1])**2)
    return round(S, 2)

