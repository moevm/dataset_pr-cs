import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    return (point1[0] <= robot[0] <= point3[0]) and (point1[1] <= robot[1] <= point3[1])

def check_collision(coefficients):
    collisions = []
    for i in range(len(coefficients)):
        for j in range(i + 1, len(coefficients)):
            a1, b1, c1 = coefficients[i]
            a2, b2, c2 = coefficients[j]
            try:
                A = np.array([[a1, b1], [a2, b2]])
                B = np.array([c1, c2])
                x = np.linalg.solve(A, B)
                collisions.append((i, j))
                collisions.append((j, i))
            except:
                ...
    return sorted(collisions)            

def check_path(points_list):
    path = 0
    for i in range(1, len(points_list)):
        x1, y1 = points_list[i - 1]
        x2, y2 = points_list[i]
        path += ((abs(x1 - x2)) ** 2 + (abs(y1 - y2)) ** 2) ** 0.5
    return round(path, 2)
