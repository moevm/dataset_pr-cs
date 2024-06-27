import numpy as np
import math

def check_collision(bot1, bot2):
    bot3=np.vstack((bot1, bot2))
    if np.linalg.matrix_rank(bot3)!=2:
        return None
    r = np.array(bot1[0:2])
    r1 = np.array(bot2[0:2])
    r2 = []
    r2.append(bot1[2])
    r2.append(bot2[2])
    r2 = np.array(r2)
    matrix = np.vstack((r, r1))
    result = np.linalg.solve(matrix, r2)
    return (-round(result[0],2), -(round(result[1],2)))

def check_surface(point1, point2, point3):
    bot3 = np.vstack((point1, point2, point3))
    if np.linalg.matrix_rank(bot3) != 3:
        return None
    r = np.array(point1[0:2])
    r=np.append(r, 1)
    r1 = np.array(point2[0:2])
    r1=np.append(r1, 1)
    r3 = np.array(point3[0:2])
    r3 = np.append(r3, 1)
    r2 = []
    r2.append(point1[2])
    r2.append(point2[2])
    r2.append(point3[2])
    matrix = np.vstack((r, r1, r3))
    result = np.linalg.solve(matrix, r2)
    return np.round(result,2)

def check_rotation(vec, rad):
    vector=np.array(vec)
    rot = np.array([[math.cos(rad), -math.sin(rad), 0], [math.sin(rad), math.cos(rad),0], [0, 0, 1]])
    result = np.dot(rot, vector)
    return np.round(result,2)
