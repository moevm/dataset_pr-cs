import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    return point1[0] <= robot[0] and  robot[0]<=point3[0] and point1[1] <= robot[1] and  robot[1]<=point3[1] 

def check_collision_pair(a,b):
    return a[0]*b[1]-a[1]*b[0]!=0    

def check_collision(coefficients):
    a=[]
    for i in range(0,len(coefficients)):
        for j in range(0,len(coefficients)):
            if i!=j and  check_collision_pair(coefficients[i],coefficients[j]):
                a+=[(i,j)]
    return a
    
    
    
def dist(x,y):
    return ((x[0]-y[0])**2+(x[1]-y[1])**2)**0.5
    
def check_path(points_list):
    a=0.0
    for i in range(0,len(points_list)-1):
        a+=dist(points_list[i], points_list[i+1])
    b=round(a,2)
    return b