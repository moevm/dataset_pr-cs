import numpy as np


def check_collision(bot1, bot2):
    equation = np.array([[bot1[0], bot1[1]],[bot2[0], bot2[1]]])
    solution = np.array([-bot1[2], -bot2[2]])
    if np.linalg.matrix_rank(equation) >= 2:
        return tuple([round(x,2) for x in np.linalg.solve(equation, solution)])
    else:
        return None


def check_surface(point1, point2, point3):
    equation = np.array([[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]])
    solution = np.array([point1[2], point2[2], point3[2]])
    if np.linalg.matrix_rank(equation) >= 3:
        return np.round(np.linalg.solve(equation, solution),2)
    else:
        return None


def check_rotation(vec, rad):
    turn = np.array([[np.cos(rad), -(np.sin(rad)), 0], [np.sin(rad), np.cos(rad), 0], [0, 0, 1]])
    map_point = np.array([vec[0], vec[1], vec[2]])
    return np.array([round(x,2) for x in turn.dot(map_point)])
