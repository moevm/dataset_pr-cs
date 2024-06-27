import numpy as np



def check_collision(bot1, bot2):
    left_side = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])  # левая часть матрицы
    right_side = np.array([-(bot1[2]), -(bot2[2])])  # правая часть матрицы
    r = np.linalg.solve(left_side, right_side)  # решение матрицы
    r = np.round(r, 2)
    return (r[0],r[1])


def check_surface(point1, point2, point3):
    a = np.array([point1, point2, point3], dtype=np.float32)
    if np.round(np.linalg.det(a), 2) != 0:
        matrix = np.array([[point1[0], point1[1], 1.], [point2[0], point2[1], 1.], [point3[0], point3[1], 1.]])
        free = np.array([point1[2], point2[2], point3[2]])
        return((np.round(np.linalg.solve(matrix, free), 2)))
    else:
        return("None")


def check_rotation(vec, rad):
    a = [[np.cos(rad), -np.sin(rad), 0], [np.sin(rad), np.cos(rad), 0], [0, 0, 1]]
    a = np.dot(a, vec)
    result = np.round(np.array(a),2)
    return result


