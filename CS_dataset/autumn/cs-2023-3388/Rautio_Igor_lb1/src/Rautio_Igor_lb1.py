import numpy
from math import *


def check_collision(bot_1, bot_2):
    b = numpy.concatenate(([bot_1], [bot_2]), axis=0)
    c = (-1) * b[:, 2]
    if (numpy.linalg.matrix_rank(b) == 2 and numpy.linalg.matrix_rank(b[:, 0:2]) == 2):
        result = tuple(round(x, 2) for x in numpy.linalg.solve(b[:, :2], c))
        return result
    else:
        return None
        
def check_surface(point_1, point_2, point_3):
    a = numpy.concatenate(([point_1], [point_2], [point_3]), axis=0)
    a = numpy.insert(a, 2, 1, axis=1)
    if (numpy.linalg.matrix_rank(a) == 3 and numpy.linalg.matrix_rank(a[:, 0:3]) == 3):
        result = numpy.array([round(x, 2) for x in numpy.linalg.solve(a[:, 0:3], a[:, 3])])
        return result
    else:
        return None

def check_rotation(vec, rad):
    vec = numpy.array([float(x) for x in vec])
    a, b = vec[0], vec[1]
    vec[0] = a * cos(rad) - b * sin(rad)
    vec[1] = b * cos(rad) + a * sin(rad)
    return numpy.array([round(x, 2) for x in vec])
