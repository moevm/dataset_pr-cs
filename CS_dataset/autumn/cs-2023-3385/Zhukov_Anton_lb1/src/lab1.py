import numpy


def check_crossroad(robot, point1, point2, point3, point4):
    all_x = point1[0], point2[0], point3[0], point4[0]
    all_y = point1[1], point2[1], point3[1], point4[1]
    min_x = min(all_x)
    max_x = max(all_x)
    min_y = min(all_y)
    max_y = max(all_y)
    return min_x <= robot[0] <= max_x and min_y <= robot[1] <= max_y


def check_collision(coefficients):
    accidents = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            det_matrix = coefficients[i][0] * coefficients[j][1] - coefficients[i][1] * coefficients[j][0]
            if det_matrix != 0 and i != j:
                accidents.append((i, j))
    return accidents


def check_path(points_list):
    length = 0
    for i in range(1,len(points_list)):
        len_x = abs(points_list[i-1][0] - points_list[i][0])
        len_y = abs(points_list[i-1][1] - points_list[i][1])
        length += numpy.sqrt(len_x ** 2 + len_y ** 2)
    return numpy.round(length, 2)
