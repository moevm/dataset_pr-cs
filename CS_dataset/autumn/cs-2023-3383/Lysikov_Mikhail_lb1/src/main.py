import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    if ((point1[0] <= robot[0] <= point2[0]) and (point1[1] <= robot[1] <= point4[1])):
        return True
    else:
        return False


def check_collision(coefficients):
    num_bots = coefficients.shape[0]
    collision_pairs = []
    for i in range(num_bots):
        for j in range(i + 1, num_bots):
            if (coefficients[i][0] / coefficients[j][0]) != (coefficients[i][1] / coefficients[j][1]):
                collision_pairs.append((i, j))
                collision_pairs.append((j, i))
                collision_pairs = sorted(collision_pairs)

    if collision_pairs:
        return collision_pairs
    else:
        return None


def check_path(points_list):
    points = np.array(points_list)
    distances = np.linalg.norm(points[1:] - points[:-1], axis=1)
    total_distance = np.sum(distances)
    rounded_distance = round(total_distance, 2)
    return rounded_distance
