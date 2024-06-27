import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    if ((robot[0]<min(point1[0], point2[0], point3[0], point4[0])) or (robot[0]> max(point1[0], point2[0], point3[0], point4[0]))) or ((robot[1]<min(point1[1], point2[1], point3[1], point4[1])) or (robot[1]> max(point1[1], point2[1], point3[1], point4[1]))):
        return False
    else:
        return True
    
def check_collision(coefficients):
    collisions=[]
    for i in range (coefficients.shape[0]):
        for k in range (coefficients.shape[0]):
            logI=coefficients[i]
            logK=coefficients[k]
            A=np.array([[logI[0], logI[1]], [logK[0], logK[1]]])
            b=np.array([logI[2], logK[2]])
            try:
                np.linalg.solve(A, b)
                collisions.append((i,k))
            except:
                pass
    return collisions
    
def check_path(points_list):
    path=0
    for i in range(len(points_list)-1):
        a1=(points_list[i][0]-points_list[i+1][0])**2
        a2=(points_list[i][1]-points_list[i+1][1])**2
        path+=np.sqrt(a1+a2)
    return round(path,2)