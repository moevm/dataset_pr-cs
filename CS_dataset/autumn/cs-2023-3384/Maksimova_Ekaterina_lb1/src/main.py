import numpy as np

def check_collision(bot1, bot2):
    coefficients = np.array([bot1[:2], bot2[:2]])
    constant = np.array([-1*bot1[2], -1*bot2[2]])
    try:
        collision = tuple([round(i, 2) for i in np.linalg.solve(coefficients, constant)])
        return collision
    except np.linalg.LinAlgError:
        return None

def check_surface(point1, point2, point3):
    coefficients = np.array([np.append(point1[:2], 1),
                             np.append(point2[:2], 1),
                             np.append(point3[:2], 1)])
    vector = np.array([point1[2], point2[2], point3[2]])
    try:
        result = np.array([round(j, 2) for j in np.linalg.solve(coefficients, vector)])
        return result
    except np.linalg.LinAlgError:
        return None

def check_rotation(vec, rad):
    c = np.cos(rad)
    s = np.sin(rad)
    matrix_rotation = np.array([[c, -s, 0], [s, c, 0], [0, 0, 1]])
    coordinates = np.dot(matrix_rotation, vec)
    return np.round(coordinates, 2)
