import numpy as np
import numpy.linalg as npl

def check_collision(bot1, bot2):
    matrix = np.array([bot1[0:2], bot2[0:2]])
    vec  = np.array([-1*bot1[-1], -1*bot2[-1]])
    if ((npl.matrix_rank(matrix) == 2)):
        return tuple([round(i, 2) for i in npl.solve(matrix, vec)])
    else:
        return None


def check_surface(point1, point2, point3):
    matrix = np.append(np.array([point1[0:2], point2[0:2], point3[0:2]]), 
                       [[1], [1], [1]], axis = 1)
    vec = np.array([point1[-1], point2[-1], point3[-1]])
    if ((npl.matrix_rank(matrix) == 3)):
        return np.array([round(i, 2) for i in npl.solve(matrix, vec)])
    else:
        return None


def check_rotation(vec, rad):
    x, y, z = vec[0], vec[1], vec [2]
    return np.array([round(x*np.cos(rad) - y*np.sin(rad), 2), 
            -1*round(-x*np.sin(rad) - y*np.cos(rad), 2), 
            round(z, 2)])