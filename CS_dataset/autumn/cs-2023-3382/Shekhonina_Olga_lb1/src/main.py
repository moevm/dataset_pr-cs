import numpy as np
def check_collision(bot1, bot2):
    arr = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    if np.linalg.matrix_rank(arr)==2:
        ans = np.array([-bot1[2], -bot2[2]])
        return tuple(round(np.linalg.solve(arr, ans)[i], 2) for i in range (2))
    else:
        return None

def check_surface(point1, point2, point3):
    arr = np.array([[point1[0], point1[1], 1],
                    [point2[0], point2[1], 1],
                    [point3[0], point3[1], 1]])
    if np.linalg.matrix_rank(arr)==3:
        ans = np.array([point1[2], point2[2], point3[2]])
        return np.array([round(np.linalg.solve(arr, ans)[i], 2) for i in range(3)])
    else:
        return None

def check_rotation(vec, rad):
    arr = np.array([[np.cos(rad), -np.sin(rad), 0],
                    [np.sin(rad), np.cos(rad), 0],
                    [0, 0, 1]])
    return np.round(arr.dot(vec), 2)