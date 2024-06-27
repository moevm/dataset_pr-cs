import numpy as np
from math import sqrt

def check_crossroad(robot, point1, point2, point3, point4):
    return (point1[0] <= robot[0] <= point3[0]) and (point1[1] <= robot[1] <= point3[1])


def check_collision(coefficients):
    arr_collisions = []
    arr_a_b = []
    arr_c = []
    arr_result = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            try:
                if i != j:
                    arr_a_b = [[coefficients[i][0],coefficients[i][1]], [coefficients[j][0],coefficients[j][1]]] 
                    arr_c = [-coefficients[i][2], -coefficients[j][2]]
                    
                    arr_result = np.linalg.solve(arr_a_b, arr_c)
                    
                    arr_collisions.append((i,j))
                else:
                    continue
            except np.linalg.LinAlgError:
                continue
    
    return arr_collisions


def check_path(points_list):
    path = 0
    for  segment_end in range(1, len(points_list)):
        path += sqrt((points_list[segment_end][0]-points_list[segment_end-1][0])**2 + (points_list[segment_end][1]-points_list[segment_end-1][1])**2)
    return round(path, 2)
