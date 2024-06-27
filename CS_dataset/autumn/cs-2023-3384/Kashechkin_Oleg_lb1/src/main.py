import numpy as np
import math

def check_crossroad(robot, point1, point2, point3, point4):
    x_r, y_r = robot
    
    if (point1[0] <= x_r <= point3[0]) and (point1[1] <= y_r <= point3[1]):
            return True
    return False
        
def check_collision(coefficients):
    size_arr = np.array(coefficients).shape
    collisions = []

    for i in range(size_arr[0]):
        for j in range(size_arr[0]):
            a1, b1, c1 = coefficients[i]
            a2, b2, c2 = coefficients[j]

            A = np.array([[a1, b1], [a2, b2]])
            B = np.array([-c1, -c2])
            
            try:
                x, y = np.linalg.solve(A, B)
                collisions.append((i, j))
            except np.linalg.LinAlgError:
                pass
            
    return collisions


def check_path(points_list):
    all_distance = 0
    
    for i in range(len(points_list) - 1):
        x1, y1 = points_list[i]
        x2, y2 = points_list[i+1]
        
        distance = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
        all_distance += distance
        round_all_distance = round(all_distance, 2)
    return round_all_distance