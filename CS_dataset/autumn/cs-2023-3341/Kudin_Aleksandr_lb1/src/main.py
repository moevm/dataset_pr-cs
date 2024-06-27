import numpy as np
import math


def check_crossroad(robot, point1, point2, point3, point4):
    if (point1[0] <= robot[0] <= point3[0] and
        point1[1] <= robot[1] <= point3[1]):
        return True
    else:
        return False



def get_vector(cf):
    dot1 = np.array( [0, -cf[2]/cf[1]] )
    dot2 = np.array( [1, (-cf[0] - cf[2]) / cf[1]] )
    return dot2 - dot1

def check_collision(coefficients):
    collisions = []
    for i in range(coefficients.shape[0]):
        for j in range(coefficients.shape[0]):
            if (i != j):
                Vi = get_vector(coefficients[i])
                Vj = get_vector(coefficients[j])
                M = np.array([Vi, Vj])
                
                
                if (np.linalg.matrix_rank(M) == 2):
                    collisions.append( (i, j) )
    return collisions

                


def check_path(points_list):
    total_distance = 0.0

    for i in range(1, len(points_list)):
        x1, y1 = points_list[i-1]
        x2, y2 = points_list[i]
        distance = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
        total_distance += distance

    return round(total_distance, 2)
