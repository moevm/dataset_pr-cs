import numpy as np


def check_collision(bot1, bot2):
    a1, b1, c1 = bot1
    a2, b2, c2 = bot2
    matrix = [[a1, b1], [a2, b2]]
    vector = [-c1, -c2]
    if np.linalg.matrix_rank(matrix) == len(matrix):
        x, y = np.linalg.solve(matrix, vector)
        return (round(x, 2), round(y, 2))


def check_surface(point1, point2, point3):
    x1, y1, z1 = point1
    x2, y2, z2 = point2
    x3, y3, z3 = point3
    matrix = [[x1, y1, 1], [x2, y2, 1], [x3, y3, 1]]
    vector = [z1, z2, z3]
    if np.linalg.matrix_rank(matrix) == len(matrix):
        a, b, c= np.linalg.solve(matrix, vector)
        return np.array((round(a, 2), round(b, 2), round(c, 2)))


def check_rotation(vec, rad):
    x, y, z = vec[0], vec[1], vec[2]
    if x < 0:
        rad = (np.arctan(vec[1]/vec[0]) + rad + np.pi)
    else:
        rad = (np.arctan(vec[1]/vec[0]) + rad)
    length = np.linalg.norm((x, y))
    return np.array((round(np.cos(rad)*length, 2), round(np.sin(rad)*length, 2), z))
