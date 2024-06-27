import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    x, y = robot
    x1, y1 = point1
    x3, y3 = point3
    if (x1 <= x <= x3) and (y1 <= y <= y3):
        return True
    else:
        return False

def check_collision(coefficients):
    ans = []
    for i in range(len(coefficients)):
        for j in range(i + 1, len(coefficients)):
            matrix = np.array([[coefficients[i][0], coefficients[i][1]], [coefficients[j][0], coefficients[j][1]]])
            b = np.array([[coefficients[i][2]], [coefficients[j][2]]])
            rang1 = np.linalg.matrix_rank(matrix)
            matrix = np.hstack((matrix, b))
            rang2 = np.linalg.matrix_rank(matrix)
            if rang1 == rang2:
                ans.append((i, j))
                ans.append((j, i))
    return sorted(ans)

def check_path(points_list):
    total_distance = 0.0
    for i in range(1, len(points_list)):
        x1, y1 = points_list[i - 1]
        x2, y2 = points_list[i]
        distance = ((x2 - x1)**2 + (y2 - y1)**2)**0.5
        total_distance += distance
    return round(total_distance, 2)
