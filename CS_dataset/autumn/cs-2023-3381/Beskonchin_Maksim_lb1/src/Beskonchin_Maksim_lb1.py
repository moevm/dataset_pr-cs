def check_crossroad(robot, point1, point2, point3, point4):
    return point1[0] <= robot[0] and point2[0] >= robot[0] and point3[1] >= robot[1] and point1[1] <= robot[1]

def check_collision(num_bots):
    return [(i, j) for i in range(len(num_bots)) for j in range(len(num_bots)) if (i != j) and ((num_bots[i][0] * num_bots[j][1] - num_bots[j][0] * num_bots[i][1]) != 0)]

def check_path(points_list):
    return round(sum([((((points_list[i + 1][0] - points_list[i][0]) ** 2) + ((points_list[i + 1][1] - points_list[i][1]) ** 2)) ** 0.5) for i in range(len(points_list) - 1)]), 2)