import numpy as np
import math

def check_crossroad(robot, point1, point2, point3, point4):
    x_robot, y_robot = robot
    x1, y1 = point1
    x2, y2 = point2
    x3, y3 = point3
    if x1 <= x_robot <= x3 and y1 <= y_robot <= y3:
        return True
    else:
        return False


def check_collision(coefficients):
    collisions = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if i != j:
                a1, b1 = coefficients[i][0], coefficients[i][1]
                a2, b2 = coefficients[j][0], coefficients[j][1]
                if (a2 * b1) - (a1 * b2) != 0:
                    collisions.append(tuple([i ,j]))
    
    return collisions

def check_path(points_list):
    distance = 0
    for i in range(1, len(points_list)):
        x1, y1 = points_list[i-1]
        x2, y2 = points_list[i]
        # Вычисляем расстояние между двумя точками
        segment_distance = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
        distance += segment_distance
    return round(distance, 2) 
