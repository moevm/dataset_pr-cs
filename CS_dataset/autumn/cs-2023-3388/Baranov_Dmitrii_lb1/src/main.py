import numpy 
from numpy import linalg 

def check_crossroad(robot, point1, point2, point3, point4):
    return (min(point1[0], point2[0])<=robot[0]) and (max(point1[0], point2[0])>=robot[0]) and (min(point2[1], point3[1])<=robot[1]) and ((max(point2[1],point3[1]))>=robot[1])

def check_collision(ndarray):
    arr=[]
    for i in range(len(ndarray)):
        for j in range(i+1, len(ndarray)):
            try:
                linalg.solve(numpy.vstack([ndarray[i][:2], ndarray[j][:2]]), numpy.hstack([ndarray[i][2], ndarray[j][2]]))
                arr.append((i, j))
                arr.append((j, i))
            except:
                pass
    return sorted(arr)

def check_path(points_list):
    Len = 0
    for i in range(len(points_list)-1):
        Len += numpy.sqrt((points_list[i+1][0]-points_list[i][0])**2+(points_list[i+1][1]-points_list[i][1])**2)
    return round(Len, 2)