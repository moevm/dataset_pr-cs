import numpy as np
def check_collision(bot1, bot2):
    A = np.array([bot1[:2], bot2[:2]])
    B = np.array([-bot1[2], -bot2[2]])
    r = np.linalg.matrix_rank(A)
    if r ==2:
        result = np.linalg.solve(A, B)
        for i in range(len(result)):
            result[i] = np.round(result[i], 2)
        result = tuple(result.tolist())
        return result
    else:
        return 'None'

def check_surface(point1, point2, point3):
    np1, np2, np3 = point1[:2], point2[:2], point3[:2]
    np1 = np.append(np1, 1)
    np2 = np.append(np2, 1)
    np3 = np.append(np3, 1)
    A = np.array([np1, np2, np3])
    B=np.array([point1[2], point2[2], point3[2]])
    r = np.linalg.matrix_rank(A)
    if r == 3:
        result = (np.linalg.solve(A, B))
        for i in range(len(result)):
            result[i] = np.round(result[i], 2)
        return result
    else:
        return 'None'

def check_rotation(vec, rad):
    A = np.array(vec)
    B = np.array([[np.cos(rad), -np.sin(rad), 0],
                  [np.sin(rad), np.cos(rad), 0],
                  [0, 0, 1]])
    result = np.dot(B, A)
    for i in range(len(result)):
        result[i] = np.round(result[i], 2)
    return result
