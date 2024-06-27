import numpy as np
import math
def solve(*arrays):
    matrix = np.array(arrays)
    coefficients = matrix[:, :-1]
    free_terms = matrix[:, -1]
    try:
        solvetion = np.linalg.solve(coefficients,free_terms)
        result = np.round(solvetion,2)
    except np.linalg.LinAlgError:
        result = None
    return result
def check_collision(bot1, bot2):
    matrix = np.array([bot1,bot2])
    try:
        collision = np.linalg.solve(matrix[:,:-1], -matrix[:,-1])
        return tuple(np.round(collision,2))
    except tuple(np.linalg.LinAlgError):
        return None
    pass

def check_surface(point1, point2, point3):
    return solve(np.insert(point1, 2, 1),
    np.insert(point2, 2, 1),
    np.insert(point3, 2, 1))
    pass



def check_rotation(vec: np.ndarray, rad: float) -> np.ndarray:
    cosi, sinu = np.cos(rad), np.sin(rad)
    rotation_matrix = np.matrix([[cosi, -sinu, 0],
                                [sinu, cosi, 0],
                                [0, 0, 1]])
    return np.round(np.dot(rotation_matrix, vec), 2)[0]
    pass