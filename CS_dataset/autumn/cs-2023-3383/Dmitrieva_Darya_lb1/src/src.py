import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    x_min = min(point1[0], point2[0], point3[0], point4[0])
    x_max = max(point1[0], point2[0], point3[0], point4[0])
    y_min = min(point1[1], point2[1], point3[1], point4[1])
    y_max = max(point1[1], point2[1], point3[1], point4[1])
    if x_min <= robot[0] <= x_max and y_min <= robot[1] <= y_max:
        return True
    else:
        return False
        
    pass



def check_collision(coefficients):
    length=0
    for i in coefficients:
        length+=1
    pairs = []
    for i in range(length):
        for j in range(i+1, length):
            rez=[]
            if i!=j:
                a = [[coefficients[i][0], coefficients[i][1]], [coefficients[j][0], coefficients[j][1]]]
                if np.linalg.matrix_rank(a)==2:
                    pairs.append((i, j))
                    pairs.append((j, i))
    pairs.sort()
    return pairs
    
    pass 

def check_path(points_list):
    points_list=list(map(list, points_list))
    diff = np.diff(points_list, axis=0)
    distances = np.linalg.norm(diff, axis=1)
    total_distance = np.sum(distances)
    return round(total_distance,2)
    pass 
