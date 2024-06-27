import numpy as np

def check_collision(bot1, bot2):
    a1, b1, c1 = bot1
    a2, b2, c2 = bot2
    a = np.array([[a1, b1], [a2, b2]])
    if np.linalg.matrix_rank(a) < 2:
        return None
    b = np.array([-c1, -c2])
    point = np.linalg.solve(a, b)
    rounded_point = np.round(point, 2)
    return tuple(rounded_point)
    
def check_surface(point1, point2, point3):
    cef_mat= np.vstack((np.hstack((point1[:2], 1)), np.hstack((point2[:2], 1)), np.hstack((point3[:2], 1))))
    stb_mat = np.vstack((point1[2], point2[2], point3[2]))
    if np.linalg.matrix_rank(cef_mat) >= 3:
        result = np.linalg.solve(cef_mat, stb_mat)
        return np.array([round(result[0][0], 2), round(result[1][0], 2), round(result[2][0], 2)])
    else:
        return None
        
def check_rotation(coordinates, angle):
    rotation_matrix = np.array([[np.cos(angle), -np.sin(angle), 0],
                                [np.sin(angle), np.cos(angle), 0],
                                [0, 0, 1]])
    rotated_coordinates = np.dot(rotation_matrix, coordinates)
    rounded_rotated_coordinates = np.round(rotated_coordinates, 2)
    return rounded_rotated_coordinates
