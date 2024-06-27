import numpy as np
import math

def check_crossroad(robot, point1, point2, point3, point4):
    ox=(robot[0]>=point1[0] and robot[0]<=point3[0])
    oy=(robot[1]>=point1[1] and robot[1]<=point3[1])
    return (ox and oy)

def check_collision(coefficients):
    ans=[]
    length=coefficients.shape[0]
    for i in range(length):
        for j in range(length):
            if i!=j:
                array_first=[[coefficients[i][0],coefficients[j][0]],[coefficients[i][1],coefficients[j][1]]]
                array_second=[coefficients[i][2],coefficients[j][2]]
                try:
                    point=np.linalg.solve(array_first,array_second)
                    ans+=[(i,j)]
                except:
                    pass
    return ans

def check_path(points_list):
    r=0
    for i in range(len(points_list)-1):
        ox=(points_list[i][0]-points_list[i+1][0])**2
        oy=(points_list[i][1]-points_list[i+1][1])**2
        r+=math.sqrt(ox+oy)
    return round(r,2)
