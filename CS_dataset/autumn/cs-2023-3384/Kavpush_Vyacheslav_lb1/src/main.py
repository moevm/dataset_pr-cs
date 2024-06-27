import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    if ((robot[0]>=point1[0]) and (robot[0]<=point3[0])) and ((robot[1]>=point1[1]) and (robot[1]<=point3[1])):
        return(True)
    else:
        return(False)

def check_collision(coefficients):
    otv = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if i == j:
                continue
            try:
                np.linalg.solve([coefficients[i][:2],coefficients[j][:2]],[coefficients[i][2],coefficients[j][2]])
                otv.append((i, j))
            except:
                pass
    return(otv)

def check_path(points_list):
    otv = 0
    for i in range(1, len(points_list)):
        otv += np.linalg.norm([points_list[i][0]-points_list[i-1][0],points_list[i][1]-points_list[i-1][1]])
    return(round(otv, 2))