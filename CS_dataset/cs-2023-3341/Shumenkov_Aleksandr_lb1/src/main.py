import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    return ((point1[1] <= robot[1] <= point3[1]) and (point1[0] <= robot[0] <= point2[0]))
    pass

def check_collision(coefficients):
    collisions=[]
    for i in range (coefficients.shape[0]):
        for k in range (coefficients.shape[0]):
            vI=coefficients[i]
            vK=coefficients[k]
            B=np.array([vI[2], vK[2]])
            A=np.array([[vI[0], vI[1]], [vK[0], vK[1]]])
            if np.linalg.matrix_rank(A) == 2:
                collisions.append((i, k))    
                pass
    return collisions

def check_path(points_list):
    p_len=0
    pnum=len(points_list)
    plist=np.array(points_list)
    for x in range(1, pnum):
        napr=plist[x]-plist[x-1]
        p_len+=np.linalg.norm(napr)
    p_len = round(p_len, 2)
    return(p_len)
    pass
