import numpy as np
#changed someone

def check_collision(b1, b2):
    b_vec = np.hstack((-b1[-1], -b2[-1]))
    a_mat = np.vstack((b1[:2], b2[:2]))
    if np.linalg.matrix_rank(a_mat) >= 2:
        return tuple(round(x, 2) for x in np.linalg.solve(a_mat, b_vec))
    return None


def check_surface(pt1, pt2, pt3):
    a_mat = np.hstack((pt1[:2], [1]))
    for pt in [pt2, pt3]:
        a_mat = np.vstack((a_mat, np.hstack((pt[:2], [1]))))
    if np.linalg.matrix_rank(a_mat) >= 3:
        b_vec = np.hstack((pt1[-1], pt2[-1], pt3[-1]))
        return np.array([round(x, 2) for x in np.linalg.solve(a_mat, b_vec)])
    return None

def check_rotation(vec, rad):
    mat_z = np.array([(np.cos(rad), -np.sin(rad), 0), (np.sin(rad), np.cos(rad), 0), (0, 0, 1)])
    return np.array([round(x, 2) for x in np.dot(mat_z, vec)])
