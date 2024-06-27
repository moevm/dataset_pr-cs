import numpy as np
def check_collision(bot1, bot2):
    matrix = np.vstack((bot1[:2], bot2[:2]))
    if (np.linalg.matrix_rank(matrix) != 2):
        return None
    else:
        answer = [-bot1[2], -bot2[2]]
        coordinates = np.linalg.solve(matrix, answer)
        coordinates = np.round(coordinates, 2)
        return tuple(coordinates)
def check_surface(point1, point2, point3):
    first = point1[2]
    second = point2[2]
    third = point3[2]
    point1[2] = 1
    point2[2] = 1
    point3[2] = 1
    matrix = np.vstack((point1, point2, point3))
    if (np.linalg.matrix_rank(matrix) != 3):
        return None
    else:
        answer = [first, second, third]
        plane = np.linalg.solve(matrix, answer)
        plane[0] = round(plane[0], 2)
        plane[1] = round(plane[1], 2)
        plane[2] = round(plane[2], 2)
        return plane
def check_rotation(vec, rad):
    turn = [[np.cos(rad), np.sin(rad), 0], [-np.sin(rad), np.cos(rad), 0], [0, 0, 1]]
    coordinates = np.dot(vec, turn)
    coordinates[0] = np.round(coordinates[0], 2)
    coordinates[1] = np.round(coordinates[1], 2)
    coordinates[2] = np.round(coordinates[2], 2)
    return coordinates
      