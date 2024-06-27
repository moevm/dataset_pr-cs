import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    if (point2[0] >= robot[0] >= point1[0]) and (point3[1] >= robot[1] >= point1[1]):
        return True
    else:
        return False
    pass


def check_collision(coefficients):
    result = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if (-(coefficients[i][0] / coefficients[i][1])) != (-(coefficients[j][0] / coefficients[j][1])):
                result.append((i, j))
    return result
    pass


def check_path(points_list):
    traveled = 0
    for i in range(len(points_list) - 1):
        vector1 = np.array(points_list[i])
        vector2 = np.array(points_list[i + 1])
        
        result_vector = vector2 - vector1
        
        traveled += np.linalg.norm(result_vector)
    return round(traveled, 2)
    pass
