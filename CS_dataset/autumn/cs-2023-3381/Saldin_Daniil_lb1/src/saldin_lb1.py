import numpy as np
def check_crossroad(robot, point1, point2, point3, point4):
    return ((point1[0] <= robot[0] <= point3[0]) and (point1[1] <= robot[1] <= point3[1]))


def check_collision(coefficients):
    ans =[]
    len_coef= len(coefficients)
    for i in range(len_coef-1):
        for j in range(i+1,len_coef):
            mt1 = np.array(([coefficients[i][0], coefficients[i][1]], [coefficients[j][0], coefficients[j][1]]))
            mt2 = np.array((coefficients[i], coefficients[j]))
            if np.linalg.matrix_rank(mt1) == np.linalg.matrix_rank(mt2):
                ans.append((i,j))
                ans.append((j,i))
    else: return sorted(ans) 


def check_path(points_list):
    path = 0
    for i in range(len(points_list)-1):
        x = points_list[i+1][0] - points_list[i][0]
        y = points_list[i+1][1] - points_list[i][1]
        path+= ((x**2 + y**2)**0.5)
    return round(path,2)
