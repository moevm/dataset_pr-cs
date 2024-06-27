import numpy as np


def check_collision(bot1, bot2):
#bot1=(a1, b1, c1);bot2=(a2, b2, c2)
#ax+by+c=0
    a1, b1, c1=bot1
    a2, b2, c2=bot2
#numpy.linalg.solve(A, v)
    A=np.array([[a1, b1], [a2, b2]])
    if np.linalg.det(A) == 0:
        return None
    v=np.array([-c1, -c2])
#если решение найти невозможно: вернуть None. 
    result=np.linalg.solve(A, v)
    result=np.round(result, 2)
    rank=np.linalg.matrix_rank(A)
    if rank<2:
        return None
    else:
        return tuple(result)
    pass


def check_surface(point1, point2, point3):
    x1, y1, z1=point1
    x2, y2, z2=point2
    x3, y3, z3=point3
    A=np.array([[x1, y1, 1], [x2, y2, 1], [x3, y3, 1]])
    if np.linalg.det(A) == 0:
        return None
    v=np.array([z1, z2, z3])
    result=np.linalg.solve(A, v)
    result=np.round(result, 2)
    rank=np.linalg.matrix_rank(A)
    if rank<2:
        return None
    else:
        return result
    pass


def check_rotation(vec, rad):
    rotation_matrix = np.array([[np.cos(rad), -np.sin(rad), 0],
[np.sin(rad), np.cos(rad), 0],
[0, 0, 1]])
    rotation=rotation_matrix.dot(vec)
    result=np.round(rotation, 2)
    rank=np.linalg.matrix_rank(rotation_matrix)
    if rank<2:
        return None
    else:
        return result
    pass

