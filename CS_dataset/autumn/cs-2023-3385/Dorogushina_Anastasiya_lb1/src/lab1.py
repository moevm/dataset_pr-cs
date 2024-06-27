import numpy as np


def check_collision(bot1, bot2):
    matrix=np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    vsk=np.array([-bot1[2], -bot2[2]])
    if (np.linalg.matrix_rank(matrix))!=2:
        return None
    else:
        res=np.linalg.solve(matrix,vsk)
        return tuple(np.around(res,2))


def check_surface(point1, point2, point3):
    matrix=np.array([[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]])
    vsk=np.array([point1[2], point2[2], point3[2]])
    if (np.linalg.matrix_rank(matrix))!=3:
        return None
    else:
        res=np.linalg.solve(matrix,vsk)
        return np.around(res,2)


def check_rotation(vec, rad):
     matrix=np.array([[np.cos(rad), -np.sin(rad), 0], [np.sin(rad), np.cos(rad), 0], [0, 0, 1]])
     res=matrix.dot(vec)
     return np.around(res,2)
