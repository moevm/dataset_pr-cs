import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    x, y = robot
    checks = [point2[0] >= x >= point1[0],
              point4[1] >= y >= point1[1]]
    return all(checks)


def check_collision(coefficients):
    answer_list = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            A = np.array([coefficients[i][:2], coefficients[j][:2]])
            if np.linalg.det(A): answer_list.append((i,j))
    return answer_list

def distance(point1, point2):
    return ((point1[0]-point2[0])**2 + (point1[1]-point2[1])**2)**0.5

def check_path(points_list):
    total_distance = 0
    for i in range(len(points_list)-1):
        total_distance += distance(points_list[i], points_list[i+1])
    return round(total_distance, 2)
