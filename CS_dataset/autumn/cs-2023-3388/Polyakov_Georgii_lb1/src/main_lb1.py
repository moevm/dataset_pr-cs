import numpy as np
from numpy import linalg

def check_crossroad(robot, point1, point2, point3, point4):
    return (point1[0]<=robot[0]<=point2[0] and point2[1]<=robot[1]<=point3[1])


def check_collision(coefficients):
    arr_collaps = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if coefficients[i][0]/coefficients[i][1] != coefficients[j][0]/coefficients[j][1]:
                arr_collaps.append((i,j))
    return arr_collaps


def check_path(points_list):
    sum_len = 0
    for i in range(len(points_list) - 1):
        x1, y1 = points_list[i]
        x2, y2 = points_list[i + 1]
        vector = (x2 - x1, y2 - y1)
        sum_len+=linalg.norm(vector)
    return round(sum_len,2)
