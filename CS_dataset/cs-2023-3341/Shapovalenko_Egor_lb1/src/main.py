import numpy as np

def check_collision(bot1, bot2):
    coefficient_matrix = np.vstack((bot1[:2], bot2[:2]))
    absolute_term_matrix = np.vstack((-bot1[2], -bot2[2]))

    if np.linalg.matrix_rank(coefficient_matrix) >= 2:
        answer = np.linalg.solve(coefficient_matrix, absolute_term_matrix)
        return (round(answer[0][0], 2), round(answer[1][0], 2))
    else:
        return None

def check_surface(point1, point2, point3):
    coefficient_matrix = np.vstack((np.hstack((point1[:2], 1)), np.hstack((point2[:2], 1)), np.hstack((point3[:2], 1))))
    absolute_term_matrix = np.vstack((point1[2], point2[2], point3[2]))

    if np.linalg.matrix_rank(coefficient_matrix) >= 3:
        answer = np.linalg.solve(coefficient_matrix, absolute_term_matrix)
        return np.array([round(answer[0][0], 2), round(answer[1][0], 2), round(answer[2][0], 2)])
    else:
        return None

def check_rotation(vec, rad):
    rotation_matrix = np.array([[np.cos(rad), -np.sin(rad), 0], [np.sin(rad), np.cos(rad), 0], [0, 0, 1]])
    vec = rotation_matrix.dot(vec)
    for i in range(3):
        vec[i] = round(vec[i], 2)
    return vec
