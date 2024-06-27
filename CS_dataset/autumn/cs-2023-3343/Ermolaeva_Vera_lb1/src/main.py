import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    if robot[0] >= point1[0] and robot[0] <= point2[0] and robot[1] >= point1[1] and robot[1] <= point4[1]:
        return True
    else:
        return False

def check_collision(coefficients):
    res = []

    for x in range(len(coefficients)):
        for y in range(len(coefficients)):

            if x==y:
                continue

            a1, b1, c1 = coefficients[x]
            a2, b2, c2 = coefficients[y]

            A = np.array([[a1, a2], [b1, b2]])
            B = np.array([[c1, c2]])

            if np.linalg.matrix_rank(A) <= np.linalg.matrix_rank(B) or not np.any(A) and not np.any(B):
                continue

            res.append(tuple([x, y]))

    return res
 
def check_path(points_list):
    z = 0
    for i in range(len(points_list)-1):
        a, b = points_list[i], points_list[i+1]
        x = abs(a[1]) - abs(b[1])
        y = abs(b[0]) - abs(a[0])

        z += np.sqrt(x**2+y**2)
    return round(z, 2)