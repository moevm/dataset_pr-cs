import numpy as np
from itertools import product

def check_crossroad(robot, point1, point2, point3, point4):
    rec_points = [point1, point2, point3, point4]

    x_vals = [pt[0] for pt in rec_points]
    y_vals = [pt[1] for pt in rec_points]

    max_x = max(x_vals)
    max_y = max(y_vals)

    min_x = min(x_vals)
    min_y = min(y_vals)

    return min_x <= robot[0] <= max_x and min_y <= robot[1] <= max_y


def check_collision(coefficients):
    collisions = []
    
    for (i, robot1), (j, robot2) in product(enumerate(coefficients), repeat=2):
        matrix = np.array([robot1, robot2])
        
        if np.linalg.matrix_rank(matrix) == 2:
            collisions.append((i, j))
    
    return collisions


def check_path(points_list):
    sum_path = 0
    
    for i in range(1, len(points_list)):
        x1, y1 = points_list[i-1]
        x2, y2 = points_list[i]
        
        dx = x2 - x1
        dy = y2 - y1
        sum_path += ((dx*dx + dy*dy) ** .5)
    
    return round(sum_path, 2)
    