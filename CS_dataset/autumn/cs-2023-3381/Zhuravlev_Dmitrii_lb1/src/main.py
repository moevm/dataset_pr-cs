import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    return (point1[0] <= robot[0] <= point2[0]) and (point1[1] <= robot[1] <= point4[1])


def check_collision(coefficients):
    ans = []
    for i in range(len(coefficients)-1):
        for j in range(i+1, len(coefficients)):
            coef = (coefficients[i][0:2], coefficients[j][0:2])
            matrix = (coefficients[i], coefficients[j])
            rank1 = np.linalg.matrix_rank(coef)
            rank2 = np.linalg.matrix_rank(matrix)
            if rank1 == rank2:
                ans.append((i, j))
                ans.append((j, i))
    return sorted(ans)


def check_path(points_list):
    ans = 0
    for i in range(len(points_list)-1):
        x = points_list[i][0] - points_list[i+1][0]
        y = points_list[i][1] - points_list[i+1][1]
        ans += np.linalg.norm((x, y))
    return round(ans, 2)
