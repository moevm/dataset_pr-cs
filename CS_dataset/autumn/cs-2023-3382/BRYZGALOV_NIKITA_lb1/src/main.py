import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    return ((point1[0] <= robot[0] <= point3[0]) and (point1[1] <= robot[1] <= point3[1]))


def check_collision(ndarray):
    pairs_of_robots, count = [], len(ndarray)
    for i in range(count):
        for j in range(count):
            matrix = np.vstack((ndarray[i][:-1], ndarray[j][:-1]))
            rank = np.linalg.matrix_rank(matrix)
            if rank >= 2: pairs_of_robots += [(i,j)]
    return pairs_of_robots


def check_path(points_list):
    distance_traveled = 0
    count = len(points_list)
    for i in range(count-1):
        point1, point2 = points_list[i], points_list[i+1]
        distance = ((point1[0]-point2[0])**2 + (point1[1]-point2[1])**2) ** 0.5
        distance_traveled += distance
    return round(distance_traveled,2)
