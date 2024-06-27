import numpy as np
import math

def check_collision(bot1,bot2):
    free_coeficients = np.array([-bot1[2],-bot2[2]])
    elder_coeficients = np.array([[bot1[0],bot1[1]], [bot2[0],bot2[1]]])
    if np.linalg.matrix_rank(elder_coeficients) >=2:
        result = np.linalg.solve(elder_coeficients, free_coeficients)
        return (round(result[0],2), round(result[1],2))
    else: return None


def check_surface(point1,point2,point3):
    matrix_coeficients = np.array([[point1[0],point1[1],1],[point2[0],point2[1],1],[point3[0],point3[1],1]])
    free_coeficients = np.array([point1[2],point2[2],point3[2]])
    if np.linalg.matrix_rank(matrix_coeficients)>=3:
        result = np.array([round(x,2) for x in np.linalg.solve(matrix_coeficients,free_coeficients)])
        return result
    else: return None


def check_rotation(vec,rad):
    rotation_matrix = np.array([[math.cos(rad), -math.sin(rad)],[math.sin(rad), math.cos(rad)]])
    vector_column = np.array([vec[0],vec[1]])
    result = np.array([round(x,2) for x in np.dot(rotation_matrix,vector_column)]+[round(vec[2],2)])
    return result
