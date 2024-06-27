import numpy as np

#задача 1
def check_collision(bot1, bot2):
    coef_с = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    if np.linalg.matrix_rank(coef_с) == 2:
        values_c = np.array([-bot1[2], -bot2[2]])
    else:
        return None
    return tuple(np.linalg.solve(coef_с, values_c).round(2))

#задача 2     
def check_surface(point1, point2, point3):
    coef_s = np.array([[point1[0], point1[1], 1],
                       [point2[0], point2[1], 1],
                       [point3[0], point3[1], 1]],
                      )
    if np.linalg.matrix_rank(coef_s) == 3:
        values_s = np.array([point1[2], point2[2], point3[2]])
    else:
        return None
    res = np.round(np.linalg.solve(coef_s, values_s), 2)
    return res

#задача 3
def check_rotation(coord, angle):
    coef_r = np.array([
        [np.cos(angle), -np.sin(angle), 0],
        [np.sin(angle), np.cos(angle), 0],
        [0, 0, 1],
        ])
    return np.round(coef_r.dot(coord), 2)
