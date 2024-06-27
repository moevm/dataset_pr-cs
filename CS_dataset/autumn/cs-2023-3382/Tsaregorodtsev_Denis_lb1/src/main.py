import numpy as np
def check_crossroad(robot, point1, point2, point3, point4):
    if (point1[0]<=robot[0]<=point3[0] and point1[1]<=robot[1]<=point3[1]):
        return True
    return False
def check_collision(coefficients):
    conflict=[]
    for i in range(len(coefficients)):
        for j in range (len(coefficients)):
            proverka=np.array((coefficients[i][:2],coefficients[j][:2]))
            if np.linalg.matrix_rank(proverka)==2:
                conflict.append((i,j))
    return conflict
def check_path(points_list):
    road=np.array(points_list)
    distance=0
    for i in range(len(road)-1,0,-1):
        distance+=np.linalg.norm(road[i-1]-road[i])
    return round(distance,2)
