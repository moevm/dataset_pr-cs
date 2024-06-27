import numpy as np

def check_collision(bot1, bot2):
    
    A = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    
    b = np.array([-bot1[2], -bot2[2]])
    
    if np.linalg.matrix_rank(A) < 2:
        
        return None
    
    try:
        intersection = np.linalg.solve(A, b)
        
        rounded_intersection = np.round(intersection, 2)
        
        return tuple(rounded_intersection)
        
    except np.linalg.LinAlgError:
        
        return None

def check_surface(pt1, pt2, pt3):
    
    x1, y1, z1 = pt1
    
    x2, y2, z2 = pt2
    
    x3, y3, z3 = pt3
    
    matrix_coeff = np.array([[x1, y1, 1], [x2, y2, 1], [x3, y3, 1]])
    
    free_vector = np.array([z1, z2, z3])

    if np.linalg.det(matrix_coeff) == 0.0:
        
        return None
        
    else:
        
        answer = np.round(np.linalg.solve(matrix_coeff, free_vector), 2)

        return answer

def check_rotation(coordinates, angle):
    
    rotation_matrix = np.array([[np.cos(angle), -np.sin(angle)], [np.sin(angle), np.cos(angle)]])
    
    rotated_coordinates = np.dot(rotation_matrix, coordinates[:2])
    
    rounded_rotated_coordinates = np.round(rotated_coordinates, 2)
    
    return np.concatenate((rounded_rotated_coordinates, coordinates[2:]))