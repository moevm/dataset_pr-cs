import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    robot_x, robot_y = robot
    point1_x, point1_y = point1
    point2_x, point2_y = point2
    point4_x, point4_y = point4
    if point1_x <= robot_x <= point2_x and point1_y <= robot_y <= point4_y:
        return True
    else:
        return False


def check_collision(coefficients):
    count_robot = coefficients.shape[0]  # количество строк = количество дакиботов
    collision = []
    for i in range(count_robot):
        for j in range(count_robot):
            if i != j:
                # проверка на параллельность прямых
                ratio_x = coefficients[i][0] / coefficients[j][0]
                ratio_y = coefficients[i][1] / coefficients[j][1]
                if ratio_x != ratio_y:
                    collision.append((i, j))
    return collision


def check_path(points_list):
    # по теореме Пифагора
    length = 0
    for i in range(len(points_list) - 1):
        x1, y1 = points_list[i]
        x2, y2 = points_list[i + 1]
        length += ((x2 - x1) ** 2 + (y2 - y1) ** 2) ** 0.5
    length = round(length, 2)
    return length
    
