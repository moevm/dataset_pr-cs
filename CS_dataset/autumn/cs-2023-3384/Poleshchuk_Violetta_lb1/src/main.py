import numpy as np

def check_collision(bot1, bot2):
    matrix_k = np.array([bot1[:-1], bot2[:-1]])
    if np.linalg.matrix_rank(matrix_k) == 2:
        vector = np.array([-bot1[-1], -bot2[-1]])
        result = np.linalg.solve(matrix_k, vector)
        return(tuple(np.round(result, decimals=2)))
    return None


def check_surface(point1, point2, point3):
    matrix_k = np.array([
        [point1[0], point1[1], 1],
        [point2[0], point2[1], 1],
        [point3[0], point3[1], 1]
    ])
    if np.linalg.matrix_rank(matrix_k)==3:
        vector = np.array([point1[-1], point2[-1], point3[-1]])
        result = np.linalg.solve(matrix_k, vector)
        return(np.round(result, decimals=2))
    return None

def check_rotation(vec, rad):
    matrix_z = np.array([
        [np.cos(rad), -np.sin(rad), 0],
        [np.sin(rad), np.cos(rad), 0],
        [0, 0, 1]
    ])

    result = np.dot(matrix_z, vec)
    return(np.round(result, decimals=2))
