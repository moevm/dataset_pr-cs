import numpy as np


def check_crossroad(robot, point1, point2, point3, point4) -> bool:
    [x, y] = robot
    x_coords = [point1[0], point3[0]]
    y_coords = [point1[1], point3[1]]
    return (x_coords[0] <= x <= x_coords[1]) and (y_coords[0] <= y <= y_coords[1])


def check_collision(coefficients:np.array) -> list:
    answer = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if i != j:
                coeffs1 = coefficients[i]
                coeffs2 = coefficients[j]
                if coeffs1[0] / coeffs1[1] != coeffs2[0] / coeffs2[1]:
                    answer.append((i, j))
    return answer


def check_path(points_list: np.array) -> float:
    length = 0
    for i in range(1, len(points_list)):
        x0, y0 = points_list[i - 1]
        x1, y1 = points_list[i]
        length += ((x1 - x0) ** 2 + (y1 - y0) ** 2) ** 0.5
    return round(length, 2)