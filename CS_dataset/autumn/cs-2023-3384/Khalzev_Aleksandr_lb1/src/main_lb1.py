import numpy as np

def check_collision(bot1, bot2):
    matr = [bot1[:2], bot2[:2]]
    if np.linalg.matrix_rank(matr) < len(matr):
        return None
    sv_el = [-1 * bot1[2], -1 * bot2[2]]
    return tuple(np.round(np.linalg.solve(matr, sv_el), 2))
    
def check_surface(point1, point2, point3):
    matr = [[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]]
    if np.linalg.matrix_rank(matr) < len(matr):
        return None
    sv_el = [point1[2], point2[2], point3[2]]
    return np.round(np.linalg.solve(matr, sv_el), 2)

def check_rotation(vec, rad):
    return np.array(np.array([round((vec[0] * np.cos(rad) - vec[1] * np.sin(rad)), 2), -1 * round((-1 * vec[0] * np.sin(rad) - vec[1] * np.cos(rad)), 2), round(vec[2], 2)]))
    

