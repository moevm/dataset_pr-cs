import numpy as np


def check_collision(bot1, bot2):
    mat_n = []
    mat_n.append(bot1[:2])
    mat_n.append(bot2[:2])
    mat = np.array(mat_n)
    p = []

    if np.linalg.matrix_rank(mat) < 2:
        return None
    x = np.linalg.solve(mat, -np.array([bot1[2], bot2[2]]))
    for i in x:
        p.append(round(i, 2))

    return tuple(p)


def check_surface(point1, point2, point3):
    a1, b1, с1 = [int(i) for i in point1]
    a2, b2, с2 = [int(i) for i in point2]
    a3, b3, с3 = [int(i) for i in point3]
    arr_1 = np.array([[a1, b1, 1], [a2, b2, 1], [a3, b3, 1]])
    arr_2 = np.array([с1, с2, с3])
    if np.linalg.matrix_rank(arr_1) < 3:
        return None
    result1 = np.linalg.solve(arr_1, arr_2)
    r = []
    for i in result1:
        r.append(round(i,2))
    result = np.array(r)
    return result


def check_rotation(vec, rad):
    mat = np.array(vec)

    matrix_pov = np.array([[np.cos(rad), np.sin(rad), 0],
                           [-np.sin(rad), np.cos(rad), 0],
                           [0, 0, 1]])

    res1 = mat.dot(matrix_pov)
    res2 = []
    for i in res1:
        res2.append(round(i, 2))
    res = np.array(res2)
    return res