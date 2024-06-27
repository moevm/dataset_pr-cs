import numpy as np


def check_collision(bot1, bot2):
    coefficient_matrix = np.array([coefficient for coefficient in [bot1[:-1], bot2[:-1]]],dtype = int)
    с_vector = np.array([[-float(bot1[-1])],[-float(bot2[-1])]],dtype = float)
    if np.linalg.matrix_rank(coefficient_matrix) < 2:
        return
    result = list((np.linalg.solve(coefficient_matrix,с_vector)))

    return (round(result[0][0],2) ,round(result[1][0],2))


def check_surface(point1, point2, point3):
    с_vector = np.array([[point1[-1]],[point2[-1]],[point3[-1]]],dtype = float)
    point1[-1] = 1
    point2[-1] = 1
    point3[-1] = 1
    coefficient_matrix = np.array([coefficient for coefficient in [point1, point2, point3]],dtype = float)
    if np.linalg.matrix_rank(coefficient_matrix) < 3:
        return 
    result = (np.round(np.linalg.solve(coefficient_matrix,с_vector),2))
    return str(np.rot90(result))[1:-1]

def check_rotation(vec, rad):
    rotation_matrix = np.array([[np.cos(rad), -np.sin(rad), 0],
                                [np.sin(rad), np.cos(rad), 0],
                                [0, 0, 1]])
    result = np.dot(rotation_matrix,vec)
    return np.array([round(result[0], 2), round(result[1], 2), round(result[2], 2)])