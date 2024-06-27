import numpy as np
import math

def check_collision(bot1, bot2):
    bot1AB = [bot1[0], bot1[1]]
    bot2AB = [bot2[0], bot2[1]]
    bot1C = -bot1[2]
    bot2C = -bot2[2]

    if np.linalg.matrix_rank([bot1AB, bot2AB]) != 2:
        return None

    collision = np.round(np.linalg.solve([bot1AB, bot2AB], [bot1C, bot2C]), 2)

    return tuple(collision)

def check_surface(point1, point2, point3):
    vect = [point1[2], point2[2], point3[2]]
    point1 = [point1[0], point1[1], 1]
    point2 = [point2[0], point2[1], 1]
    point3 = [point3[0], point3[1], 1]

    if np.linalg.matrix_rank([point1, point2, point3]) != 3:
        return None

    surface = np.round(np.linalg.solve([point1, point2, point3], vect), 2)

    return surface

def check_rotation(vec, rad):
    vect2D = [vec[0], vec[1]]
    col1 = [math.cos(rad), math.sin(rad)]
    col2 = [-math.sin(rad), math.cos(rad)]

    rotation = np.round(np.linalg.solve([col1, col2], vect2D), 2)

    vect3D = np.array([rotation[0], rotation[1], vec[2]])

    return vect3D