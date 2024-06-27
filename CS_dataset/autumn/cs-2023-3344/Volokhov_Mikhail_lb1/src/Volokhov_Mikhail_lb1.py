import numpy as np


def check_collision(bot1, bot2):
    a = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    b = np.array([-bot1[2], -bot2[2]])

    if np.linalg.matrix_rank(a) < 2:
        return None

    intersection = np.linalg.solve(a, b)
    intersection = tuple(round(value, 2) for value in intersection)

    return intersection



def check_surface(point1, point2, point3):
    A = np.array([[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]])
    B = np.array([point1[2], point2[2], point3[2]])
    
    if np.linalg.matrix_rank(A) == 3:
        solution = np.linalg.solve(A, B)
        return np.round(solution, 2)
    else:
        return None



def check_rotation(coordinates, angle):
    rotation_matrix = np.array([[np.cos(angle), -np.sin(angle), 0], [np.sin(angle), np.cos(angle), 0], [0, 0, 1]])
    rotated_coordinates = np.dot(rotation_matrix, coordinates)
    rotated_coordinates = np.round(rotated_coordinates, 2)

    return rotated_coordinates
