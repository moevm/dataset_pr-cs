import numpy as np

def check_collision(bot1, bot2):
    K = np.array([
        [bot1[0], bot1[1]], 
        [bot2[0], bot2[1]]])

    if np.linalg.matrix_rank(K) == 2:
        v = np.array([-bot1[2], -bot2[2]])
        return tuple(np.linalg.solve(K, v).round(2))
    else:
        return None

def check_surface(point1, point2, point3):
    K_mat = np.vstack((point1, point2, point3))
    K_mat[0][2], K_mat[1][2], K_mat[2][2] = 1, 1, 1
    if np.linalg.matrix_rank(K_mat) == 3:
        v = np.array([point1[2], point2[2], point3[2]])
        return np.array(np.linalg.solve(K_mat, v).round(2))
    else:
        return None

def check_rotation(arr, ang):
    res = np.array([
        [np.cos(ang), -np.sin(ang), 0],
        [np.sin(ang), np.cos(ang), 0],
        [0, 0, 1]])

    return np.round(res.dot(arr), 2)
