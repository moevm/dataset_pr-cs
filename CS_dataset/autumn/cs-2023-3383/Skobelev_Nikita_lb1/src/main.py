import numpy as np


def check_collision(bot1, bot2):
    arr = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    c = np.array([-1 * bot1[2], -1 * bot2[2]])
    if (np.linalg.matrix_rank(arr) >= len(arr) and np.linalg.matrix_rank(arr) >= len(arr[0])):
        res = np.linalg.solve(arr, c)
        for i in range(len(res)):
            res[i] = round(res[i], 2)
        return (tuple(res))
    else:
        return ('None')


def check_surface(point1, point2, point3):
    arr = np.array([[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]])
    z = np.array([point1[2], point2[2], point3[2]])
    if (np.linalg.matrix_rank(arr) >= len(arr) and np.linalg.matrix_rank(arr) >= len(arr[0])):
        res = np.linalg.solve(arr, z)
        for i in range(len(res)):
            res[i] = round(res[i], 2)
        return (res)
    else:
        return ('None')


def check_rotation(vec, rad):
    mat = np.array([[np.cos(rad), -1 * np.sin(rad), 0], [np.sin(rad), np.cos(rad), 0], [0, 0, 1]])
    res = np.dot(mat, vec)
    for i in range(len(res)):
        res[i] = round(res[i], 2)
    return (res)

