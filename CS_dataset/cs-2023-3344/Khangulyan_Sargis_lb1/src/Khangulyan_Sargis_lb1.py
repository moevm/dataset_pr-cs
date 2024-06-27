import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    arr = sorted([point1, point2, point3, point4])
    if arr[0][0] <= robot[0] <= arr[3][0] and arr[0][1] <= robot[1] <= arr[3][1]:
        return True
    else:
        return False

def check_collision(coefficients):
    otv = []
    c = coefficients
    for i1 in range(len(c)):
        for i2 in range(len(c)):
            if (c[i1] != c[i2]).any():
                mtr = np.array([c[i1], c[i2]])
                if np.linalg.matrix_rank(mtr) >= 2 and (c[i1][0] / c[i2][0]) != (c[i1][1] / c[i2][1]):
                    otv.append((i1, i2))
    return sorted(otv)

def check_path(points_list):
    otv = 0
    for i in range(len(points_list)-1):
        x = points_list[i+1]
        x0 = points_list[i]
        s = ((x[0]-x0[0])**2 + (x[1]-x0[1])**2)**(1/2)
        otv += s
    return round(otv, 2)