import numpy as np

def check_collision(bot1, bot2):
    bots = np.vstack([bot1, bot2])
    M = np.array([bot[:-1] for bot in bots])
    if np.linalg.matrix_rank(M) < len(M):
        return None
    v = np.array([-bot[-1] for bot in bots])
    return tuple(round(n, 2) for n in np.linalg.solve(M, v))

def check_surface(point1, point2, point3):
    points = np.vstack([point1, point2, point3])
    M = np.array([[*point[:-1], 1] for point in points])
    if np.linalg.matrix_rank(M) < len(M):
        return None
    v = np.array([point[-1] for point in points])
    return np.round(np.linalg.solve(M, v), 2)

def check_rotation(vec, rad):
    M_rotation = np.array([[np.cos(rad), -np.sin(rad), 0],
                           [np.sin(rad), np.cos(rad), 0],
                           [0, 0, 1]])
    return np.round(np.dot(M_rotation, vec), 2)
