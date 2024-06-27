import numpy as np
from numpy import linalg as LA
from math import cos, sin

def check_collision(bot1, bot2):    
    result = None
    if LA.matrix_rank(np.array([bot1, bot2])) == 2:
        a = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
        b = np.array([-bot1[2], -bot2[2]])
        result = tuple(LA.solve(a, b).round(2))
    return result

def check_surface(point1, point2, point3):
    result = None
    a = np.array([[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]])
    b = np.array([point1[2], point2[2], point3[2]])
    if LA.matrix_rank(a) == 3:
        result = np.array(LA.solve(a, b).round(2))
    return result

def check_rotation(vec, rad):
    x, y, z = vec[0], vec[1], vec[2]
    
    x1 = x*cos(rad) - y*sin(rad)
    y1 = x*sin(rad) + y*cos(rad)

    return np.array([x1, y1, z]).round(2)
