import numpy as np


def check_collision(bot1, bot2):
    
    a1, b1, c1 = bot1
    a2, b2, c2 = bot2
    
    x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1)
    y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1)
    
    return round(x, 2), round(y, 2)


def check_surface(point1, point2, point3):
    matrix = np.array([[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]])
    vector = np.array([point1[-1], point2[-1], point3[-1]])
    
    rank = np.linalg.matrix_rank(matrix)
    variables_count = matrix.shape[1]
    solution_possible = rank == variables_count
    
    if solution_possible:    
        solution = np.linalg.solve(matrix, vector) 
        rounded_solution = np.round(solution, 2)
        return rounded_solution
    else:
        return None


def check_rotation(vec, rad):
    rotation_matrix = np.array([[np.cos(rad), -np.sin(rad), 0],
                                [np.sin(rad), np.cos(rad), 0],
                                [0, 0, 1]])
    
    rotated_coordinates = np.dot(rotation_matrix, vec)
    rounded_rotated_coordinates = np.round(rotated_coordinates, 2)
    
    return rounded_rotated_coordinates

