import numpy as np
from math import *

def check_collision(bot1, bot2):    #print(check_collision(([-3, -6, 9]), ([8, -7, 0])))
    a1, a2, a3 = map(int, bot1)
    b1, b2, b3 = map(int, bot2)
    array1 = np.array([[a1, a2], [b1, b2]])
    array2 = np.array([-a3, -b3])
    if np.linalg.matrix_rank(array1) < 2:
        return None
    
    answer = np.linalg.solve(array1, array2)
    return (round(answer[0], 2), round(answer[1], 2))

def check_surface(point1, point2, point3):  #print(check_surface(([1, -6,  1]), ([0, -3,  2]), ([-3,  0, -1])))
    a1, b1, c1 = map(int, point1)
    a2, b2, c2 = map(int, point2)
    a3, b3, c3 = map(int, point3)
    array1 = ([[a1, b1, 1], [a2, b2, 1], [a3, b3, 1]])
    array2 = ([c1, c2, c3])
    if np.linalg.matrix_rank(array1) < 3:
        return None
    
    answer = np.linalg.solve(array1, array2)
    return (np.array([round(answer[0], 2), round(answer[1], 2), round(answer[2], 2)]))

def check_rotation(coordinates, radiants):  #print(check_rotation([1, -2, 3], 1.57))
    array = np.array([[cos(radiants), -sin(radiants), 0], [sin(radiants), cos(radiants), 0], [0, 0, 1]])
    
    answer = np.dot(array, coordinates)
    return (np.array([round(answer[0], 2), round(answer[1], 2), round(answer[2], 2)]))
