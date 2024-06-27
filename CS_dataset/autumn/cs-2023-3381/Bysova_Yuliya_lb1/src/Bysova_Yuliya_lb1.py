import numpy as np
def check_crossroad(robot, point1, point2, point3, point4):
    return ((robot[0] <= point2[0] and robot[0] >= point1[0]) and
(robot[1] >= point1[1] and robot[1] <= point4[1]))


def check_collision(coefficients):
    ans = []
    for i in range(0, len(coefficients)):
        for j in range(i + 1, len(coefficients)):
            m = np.array([[coefficients[i][0], coefficients[i][1]],
[coefficients[j][0], coefficients[j][1]]])
            v = np.array([coefficients[i][2], coefficients[j][2]])
            try:
                np.linalg.solve(m, v)
                ans.append((i, j))
                ans.append((j, i))
            except:
                pass
    return sorted(ans)
    
    
def check_path(points_list):
    len_path = 0
    for i in range(0, len(points_list) - 1):
        len_path += np.sqrt((points_list[i + 1][0] -
points_list[i][0]) ** 2 + (points_list[i + 1][1] - points_list[i][1]) ** 2)
    return np.round(len_path, 2)