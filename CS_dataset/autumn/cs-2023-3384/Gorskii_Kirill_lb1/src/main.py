import numpy as np
import math

def check_collision(bot1, bot2):
    if np.linalg.matrix_rank(np.vstack([bot1, bot2])) != 2:
        return None
    
    coeff_mat = np.vstack([bot1[0:2], bot2[0:2]])
    const_mat = np.vstack([-bot1[2], -bot2[2]])
    
    res = np.linalg.solve(coeff_mat, const_mat)
    return (round(res[0][0], 2), round(res[1][0], 2))

def check_surface(point1, point2, point3):
    coeff_mat = np.vstack([
        np.hstack([point1[0:2], 1]),
        np.hstack([point2[0:2], 1]),
        np.hstack([point3[0:2], 1])
    ])

    const_mat = np.vstack([point1[2], point2[2], point3[2]])

    if np.linalg.matrix_rank(
                np.hstack([coeff_mat, const_mat])) != 3:
        return None

    res = np.linalg.solve(coeff_mat, const_mat)
    return np.around(np.transpose(res)[0], 2)

def check_rotation(pos, angle):
    c = math.cos(angle)
    s = math.sin(angle)
    
    rotz_matrix = np.array([
        [c, -s,  0],
        [s,  c,  0],
        [0,  0,  1]
    ])

    res = rotz_matrix.dot(pos)
    return np.around(res, 2)