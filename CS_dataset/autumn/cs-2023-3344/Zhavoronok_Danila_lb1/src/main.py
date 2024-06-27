import numpy as np

def check_collision(pos1, pos2):
    a = np.array([pos1[:2], pos2[:2]])
    b = np.array([-pos1[2], -pos2[2]])

    if np.linalg.matrix_rank(a) < 2:
        return None
    
    return tuple(np.round(np.linalg.solve(a, b), 2))

def check_surface(A, B, C):
    m = np.hstack((np.array([A[:2], B[:2], C[:2]]), np.array([[1], [1], [1]])))
    v = np.array([A[2], B[2], C[2]])

    if np.linalg.matrix_rank(m) < 3:
        return None
    
    return np.round(np.linalg.solve(m, v), 2)

def check_rotation(pos, alfa):
    rotation = np.array([[np.cos(alfa), -1 * np.sin(alfa)], [np.sin(alfa), np.cos(alfa)]])
    return np.round(np.append(np.dot(rotation, pos[:2]), pos[2]), 2)
