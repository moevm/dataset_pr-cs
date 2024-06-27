import numpy as np


def check_collision(bot1, bot2):

    points = np.vstack((bot1[0:2], bot2[0:2]))
    vector = np.array([-bot1[-1], -bot2[-1]])
    if np.linalg.matrix_rank(points) >= 2:
        ans = (round(np.linalg.solve(points, vector)[0], 2), round(np.linalg.solve(points, vector)[1],2))
        return ans
    else:
        return None

def check_surface(point1, point2, point3):

    vector = np.array([point1[-1], point2[-1], point3[-1]])
    point1[-1] = 1
    point2[-1] = 1
    point3[-1] = 1
    points = np.vstack((point1, point2, point3))

    if np.linalg.matrix_rank(points) >= 3:
        return np.array([round(np.linalg.solve(points, vector)[0], 2), round(np.linalg.solve(points, vector)[1], 2), round(np.linalg.solve(points, vector)[2], 2)])
    else:
        return None

def check_rotation(vec, rad):

    return np.array([round(vec[0] * np.cos(rad) - vec[1] * np.sin(rad), 2), round(vec[0] *  np.sin(rad) + vec[1] * np.cos(rad), 2), round(vec[2],2)])
