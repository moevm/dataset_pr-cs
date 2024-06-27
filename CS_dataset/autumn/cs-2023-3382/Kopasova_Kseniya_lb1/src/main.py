import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    if (int(point3[0])>=int(robot[0])) and (int(robot[0])>=int(point1[0])) and (int(point1[1])<=int(robot[1])) and (int(robot[1])<=int(point3[1])):
        return True
    else:
        return False

def check_collision(coefficients):
    result=[]
    for i in range(len(coefficients)):
        for j in range(i+1, len(coefficients)):
            a = np.array([[coefficients[i][0], coefficients[i][1]], [coefficients[j][0], coefficients[j][1]]])
            b = np.array([coefficients[i][2], coefficients[j][2]])
            try:
                np.linalg.solve(a, b)
                result.append((i, j))
                result.append((j, i))
            except:
                pass
    return sorted(result)

def check_path(points_list):
    s=0
    for i in range(len(points_list)-1):
        v=(points_list[i][0]-points_list[i+1][0], points_list[i][1]-points_list[i+1][1])
        s+=np.linalg.norm(v)
    return round(s, 2)