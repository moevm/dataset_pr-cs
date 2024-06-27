import numpy as np

def check_collision(bot1, bot2):
    a1, b1, c1 = bot1
    a2, b2, c2 = bot2

    if np.linalg.matrix_rank(np.array([bot1, bot2])) < 2:
        return None

    x = round(((b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1)),2)
    y = round(((c1 * a2 - c2 * a1) / (a1 * b2 - a2 * b1)),2)
    return (x, y)

def check_surface(point1, point2, point3):
    b = np.hstack([point1[2],point2[2],point3[2]])

    if np.linalg.matrix_rank(np.array([point1, point2, point3])) < 3:
        return None

    point1[2] = 1
    point2[2] = 1
    point3[2] = 1
    a = np.vstack((point1, point2, point3))
    cof = np.linalg.solve(a,b)
    rcof = np.round(cof, 2)
    return rcof

def check_rotation(vec, rad):
    c, s = np.cos(rad), np.sin(rad)
    m = np.array(([c, -s, 0], [s, c, 0], [0, 0, 1]))
    newc = np.dot(m, vec)
    rnewc = np.round(newc, 2)
    return rnewc
