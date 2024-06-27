import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    return all(robot[i] <= max(point1[i], point2[i], point3[i], point4[i]) and robot[i] >= min(point1[i], point2[i], point3[i], point4[i]) for i in range(2))


def check_collision(robot_trajectories):
    uncollised_robots = []
    for i in range(len(robot_trajectories)):
        for j in range(len(robot_trajectories)):
            if i!=j and (robot_trajectories[i][0] / robot_trajectories[i][1] != robot_trajectories[j][0] / robot_trajectories[j][1] or \
            (robot_trajectories[i][0] / robot_trajectories[i][1] == robot_trajectories[j][0] / robot_trajectories[j][1] and \
             robot_trajectories[i][2] / robot_trajectories[i][1] == robot_trajectories[j][2]) / robot_trajectories[j][1]):
                uncollised_robots.append((i,j))
    return uncollised_robots


def check_path(points_list):
    total_distance = 0
    for i in range(len(points_list)-1):
        total_distance += np.linalg.norm(np.array(points_list[i+1]) - np.array(points_list[i]))
    return np.round(total_distance, 2)
