import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    crossroad = np.array([point1, point2, point3, point4])
    robotcoord = np.array(robot)
    if (robotcoord[0] >= np.min(crossroad[:, 0]) and robotcoord[0] <= np.max(crossroad[:, 0]) and
        robotcoord[1] >= np.min(crossroad[:, 1]) and robotcoord[1] <= np.max(crossroad[:, 1])):
        return True
    else:
        return False

def check_collision(coefficients):
    N = coefficients.shape[0]
    collision_pairs = []
    for bot1 in range(N):
        for bot2 in range(N):
            if bot1 != bot2:
                a1, b1, c1 = coefficients[bot1]
                a2, b2, c2 = coefficients[bot2]
                if a1 * b2 != a2 * b1:
                    collision_pairs.append((bot1, bot2))
    return collision_pairs

def check_path(points_list):
    total_distance = 0.0
    for i in range(1, len(points_list)):
        point1 = np.array(points_list[i-1])
        point2 = np.array(points_list[i])
        distance = np.linalg.norm(point2 - point1)
        total_distance += distance
    return round(total_distance, 2)
