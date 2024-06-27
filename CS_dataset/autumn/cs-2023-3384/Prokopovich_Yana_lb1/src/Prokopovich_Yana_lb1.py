import numpy
import math


def check_crossroad(robot, point1, point2, point3, point4):
    x, y = robot
    if point1[0] <= x <= point3[0] and point2[1] <= y <= point4[1]:
        return True
    return False


def check_collision(coefficients):
    answer = []
    for i in range(len(coefficients)):
        for j in range(i+1, len(coefficients)):
            a1 = numpy.array([[coefficients[i][0], coefficients[i][1]], [coefficients[j][0], coefficients[j][1]]])
            a2 = numpy.array([[coefficients[i][2]], [coefficients[j][2]]])
            if numpy.linalg.matrix_rank(a1) == 2:
                answer.append((i, j))
                answer.append((j, i))
    answer = sorted(answer)
    return answer


def check_path(points_list):
    full_path = 0
    for i in range(len(points_list)-1):
        x1, y1 = map(float, points_list[i])
        x2, y2 = map(float, points_list[i+1])
        cur_path = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
        full_path += cur_path
    full_path = round(full_path, 2)
    return full_path
