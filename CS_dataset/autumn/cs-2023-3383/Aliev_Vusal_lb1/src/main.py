import numpy as np


def check_collision(bot1, bot2):
    mat_2 = np.array([-bot1[-1],  -bot2[-1]], dtype = int)
    mat_1 = np.array([bot1[:2], bot2[:2]], dtype = int)
    if np.linalg.matrix_rank(mat_1) < mat_1.shape[0]:
        return None
    result = np.round(np.linalg.solve(mat_1,mat_2),2)
    return tuple(result)

def check_surface(point1, point2, point3):
    mat_2 = np.array([point1[-1], point2[-1], point3[-1]], dtype = int)
    mat_1 = np.array([point1[:2], point2[:2], point3[:2]], dtype = int)
    mat_ones = np.ones((3,1),dtype = int)
    mat_1 = np.hstack([mat_1,mat_ones])
    if np.linalg.matrix_rank(mat_1) < mat_1.shape[0]:
        return None
    result = np.round(np.linalg.solve(mat_1,mat_2),2)
    return result


def check_rotation(vec, rad):
    mat_1 = np.array([
        [np.cos(rad), -np.sin(rad), 0],
        [np.sin(rad), np.cos(rad), 0],
        [0, 0, 1]
    ])
    result = np.round(np.dot(mat_1, vec),2)
    return result