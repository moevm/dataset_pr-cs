import numpy as np


def check_collision(bot1, bot2):
    a = [[bot1[0], bot1[1]], [bot2[0], bot2[1]]] 
    b = [[-bot1[2]], [-bot2[2]]] 
    if np.linalg.matrix_rank(a) < 2: 
        return(None) 
    else: 
        x = np.linalg.solve(a, b) 
        return(tuple((round(x[0][0], 2), (round(x[1][0], 2))))) 


def check_surface(point1, point2, point3):
    a = [[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1],1]] 
    b = [[point1[2]], [point2[2]], [point3[2]]] 
    if np.linalg.matrix_rank(a) < 3: 
        return(None) 
    else: 
        x = np.linalg.solve(a, b) 
        return(np.array([round(x[i][0], 2) for i in range(0,3)]))


def check_rotation(vec, rad):
    return(np.array([round(vec[0]*np.cos(rad) - vec[1]*np.sin(rad),2), round(vec[0]*np.sin(rad) + vec[1]*np.cos(rad),2), round(vec[2], 2)])) 
