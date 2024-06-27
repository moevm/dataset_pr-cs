import numpy as np
def check_crossroad(robot, point1, point2, point3, point4):
    return ((point1[0] <= robot[0] <= point2[0]) and (point1[1] <= robot[1] <= point3[1]))
def check_collision(coefficients):
    collision_pairs = []
    for i, bot1 in enumerate(coefficients):
        for j, bot2 in enumerate(coefficients):
            if i != j:
                a1, b1, c1 = bot1
                a2, b2, c2 = bot2
                determinant = a1 * b2 - a2 * b1
                if determinant != 0:
                    collision_pairs.append((i, j))
    return collision_pairs
def check_path(points_list):
    diff = np.diff(np.array(points_list), axis=0)
    total_distance = np.sum(np.linalg.norm(diff, axis=1))
    return round(total_distance, 2)