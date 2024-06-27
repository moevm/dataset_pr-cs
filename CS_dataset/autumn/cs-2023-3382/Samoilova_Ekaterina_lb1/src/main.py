import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    if (int(robot[0])>=int(point1[0])) and (int(robot[0])<=int(point2[0])) and (int(robot[1])>=int(point1[1])) and (int(robot[1])<=int(point4[1])):
        return True
    else:
        return False


def check_collision(coefficients):
    res=[]
    for i in range(len(coefficients)):
        for j in range(i+1, len(coefficients)):
            a = np.array([[coefficients[i][0], coefficients[i][1]],[coefficients[j][0], coefficients[j][1]]])
            b = np.array([coefficients[i][2], coefficients[j][2]])
            try:
                np.linalg.solve(a, b)
                res.append((i, j))
                res.append((j, i))
            except:
                pass
    return sorted(res)
        


def check_path(points_list):
    lens=0
    for i in range(len(points_list)-1):
        a=(points_list[i][0]-points_list[i+1][0], points_list[i][1]-points_list[i+1][1])
        lens+=np.linalg.norm(a)
    return round(lens, 2)

        

