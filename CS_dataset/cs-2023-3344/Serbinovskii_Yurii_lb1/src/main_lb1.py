import numpy as np


def check_collision(bot1, bot2):
    vec = np.array([-bot1[2], -bot2[2]])
    M_line = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    if np.linalg.matrix_rank(M_line) < 2:
        return None
    else:
        return tuple(np.round(np.linalg.solve(M_line, vec), 2))
    pass


def check_surface(point1, point2, point3):
    vec = np.array([point1[2],point2[2],point3[2]])
    M_surf = np.array([[point1[0],point1[1], 1], [point2[0],point2[1],1], [point3[0],point3[1], 1]])
    if np.linalg.matrix_rank(M_surf) < 3:
        return None
    else:
        return np.round(np.linalg.solve(M_surf, vec), 2)
    pass


def check_rotation(vec, rad):
    M_rot = np.array([[np.cos(rad), np.sin(rad)], [-np.sin(rad), np.cos(rad)]])
    new_xy = np.round(np.linalg.solve(M_rot, [vec[0], vec[1]]), 2)
    return np.hstack([new_xy, [vec[2]]])
    pass

