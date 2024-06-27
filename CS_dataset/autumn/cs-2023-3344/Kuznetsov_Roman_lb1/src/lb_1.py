import numpy as np
import math

def check_crossroad(robot, point1, point2, point3, point4):
    rx, ry = robot
    x = sorted([point1[0], point2[0], point3[0], point4[0]])
    y = sorted([point1[1], point2[1], point3[1], point4[1]])
    return x[0] <= rx <= x[3] and y[0] <= ry <= y[3]



def check_collision(coefficients):
    crashed_robots = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if (coefficients[i][0]/coefficients[i][1]) != (coefficients[j][0]/coefficients[j][1]):
                    crashed_robots.append((i, j))
    return crashed_robots


def check_path(points_list):
    path_length= 0
    for i in range(1,len(points_list)):
        point1=points_list[i-1]
        point2=points_list[i]
        path_length += math.sqrt((point1[0]-point2[0]) ** 2 + (point1[1]-point2[1]) ** 2)
    return round(path_length, 2)
