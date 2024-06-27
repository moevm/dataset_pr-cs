import numpy as np


def check_collision(bot1, bot2):
    coefficients = np.array((bot1[:2], bot2[:2]))
    values = np.array((-bot1[-1], -bot2[-1]))

    if np.linalg.matrix_rank(coefficients) < coefficients.shape[0]:
        return None

    return tuple(np.linalg.solve(coefficients, values).round(2))


def check_surface(point1, point2, point3):
    values = np.array((point1[-1], point2[-1], point3[-1]))

    for point in [point1, point2, point3]:
        point[-1] = 1

    coefficients = np.array((point1, point2, point3))

    if np.linalg.matrix_rank(coefficients) < coefficients.shape[0]:
        return None

    return np.linalg.solve(coefficients, values).round(2)


def check_rotation(vec, rad):
    rotation = np.array(((np.cos(rad), -np.sin(rad), 0),
                         (np.sin(rad), np.cos(rad), 0),
                         (0, 0, 1)))

    return np.dot(rotation, vec).round(2)

