import numpy as np

def check_collision(bot1, bot2):
    a1, b1, c1 = bot1
    a2, b2, c2 = bot2
    coefficient_matrix = np.array([[a1, b1], [a2, b2]])
    constants = np.array([-c1, -c2])
    
    try:
        intersection = np.linalg.solve(coefficient_matrix, constants)
        intersection = np.round(intersection, 2)
        return tuple(intersection)
    except np.linalg.LinAlgError:
        return None


def check_surface(point1, point2, point3):
    points_matrix = np.array([point1, point2, point3])

    coefficients_matrix = np.column_stack((points_matrix[:, 0], points_matrix[:, 1], np.ones(3)))

    rank_coefficients = np.linalg.matrix_rank(coefficients_matrix)

    free_terms = points_matrix[:, 2]

    if rank_coefficients == 3:
        abc = np.linalg.solve(coefficients_matrix, free_terms)
        return np.round(abc, 2)
    else:
        return None
def check_rotation(coordinates, angle):
    rotation_matrix = np.array([[np.cos(angle), -np.sin(angle), 0], [np.sin(angle), np.cos(angle), 0], [0, 0, 1]])
    rotated_coordinates = np.dot(rotation_matrix, coordinates)
    rotated_coordinates = np.round(rotated_coordinates, 2)
    return rotated_coordinates