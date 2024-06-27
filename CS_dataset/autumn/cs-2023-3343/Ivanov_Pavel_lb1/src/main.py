import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    horizontal_down = point1[1]
    horizontal_up = point4[1]

    vertical_left = point1[0]
    vertical_right = point2[0]

    between_horizontal = horizontal_down <= robot[1] <= horizontal_up
    between_vertical = vertical_left <= robot[0] <= vertical_right

    return between_horizontal and between_vertical

def check_collision(coefficients_np):
    res = []
    coefficients = coefficients_np.tolist()
    for first in range(len(coefficients)):
        for second in range(len(coefficients)):
            if first == second:
                continue

            a = np.array([coefficients[first][0:-1], coefficients[second][0:-1]])
            b = np.array([coefficients[first][-1], coefficients[second][-1]])

            try:
                np.linalg.solve(a, b)
                res.append((first, second))
            except np.linalg.LinAlgError:
                continue
    return res

def check_path(points_list):
    way = 0
    for i in range(len(points_list) - 1):
        first_point = points_list[i]
        second_point = points_list[i+1]

        y_diff = first_point[1] - second_point[1]
        x_diff = first_point[0] - second_point[0]

        way += (y_diff**2 + x_diff**2)**0.5
    return round(way, 2)