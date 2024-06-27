import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    return point1[0] <= robot[0] <= point2[0] and \
    point1[1] <= robot[1] <= point4[1]

def check_collision(coefficients):
    ans = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if i != j:
                mat = np.array([coefficients[i][0:2],coefficients[j][0:2]])
                if np.linalg.matrix_rank(mat) == 2: ans.append((i,j))
    return ans

def check_path(points_list):
    sum_path = 0
    for i in range(1,len(points_list)):
        sum_path += ((points_list[i][0]-points_list[i-1][0])**2 + (points_list[i][1]-points_list[i-1][1])**2)**0.5
    return round(sum_path,2)
